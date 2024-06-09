library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity dram is
    port (
        reset : in std_logic;
        wr    : in std_logic;  -- Write enable
        addr  : in std_logic_vector(7 downto 0);
        en_mem : in std_logic;
        data  : inout std_logic_vector(7 downto 0)
    );
end dram;

architecture behavior of dram is
    type ram_type is array (255 downto 0) of std_logic_vector(7 downto 0);
    signal RAM : ram_type;
    signal data_out : std_logic_vector(7 downto 0);
    signal data_en : std_logic;
begin
    process(reset, addr, wr, en_mem)
    begin
		if en_mem = '0' then
			if reset = '0' then
				for i in 0 to RAM'high loop
				RAM(i) <= (others => '0');
				end loop;

			elsif rising_edge(wr) then
				if wr = '0' then
					RAM(conv_integer(addr)) <= data;
				end if;
			end if;
		end if;
    end process;

    process(addr, wr, en_mem)
    begin 
		if en_mem = '0' then
			if wr = '1' then
				data_out <= RAM(conv_integer(addr));
			else
				data_out <= (others => 'Z');
			end if;
        end if;
    end process;

	data <= data_out when (wr = '1' and en_mem = '0') else (others => 'Z');

end behavior;
