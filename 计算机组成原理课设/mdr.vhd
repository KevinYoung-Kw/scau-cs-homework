library ieee;
use ieee.std_logic_1164.all;

entity mdr is
	port(
		alu_out:   in std_logic_vector(7 downto 0);
		data_bus:  in std_logic_vector(7 downto 0);
		rec:       in std_logic_vector(1 downto 0);
		clk, reset: in std_logic;
		en_bus:    out std_logic;
		q:         out std_logic_vector(7 downto 0)
	);
end mdr;

architecture behave of mdr is
begin
	process(clk, reset)
	begin
		if reset = '0' then
			q <= "00000000";  -- 8 bits reset value
		elsif clk'event and clk = '1' then
			case rec is
				when "01" =>
					q <= data_bus;
					en_bus <= '1';
				when "11" =>
					q <= alu_out;
					en_bus <= '0';
				when others =>
					en_bus <= 'Z';
					null;
			end case;
		end if;
	end process;
end behave;
