library ieee;
use ieee.std_logic_1164.all;

entity ar is
	port(alu_out:    in std_logic_vector(7 downto 0);
	     pc:         in std_logic_vector(7 downto 0);
	     rec:        in std_logic_vector(1 downto 0);
	     clk, reset: in std_logic;
	     en_mem:    out std_logic;
	     q:         out std_logic_vector(7 downto 0));
	     
end ar;

architecture behave of ar is
begin
	process(clk, reset)
	begin
		if reset = '0' then
			q <= "00000000";  -- 8 bits reset value
		elsif clk'event and clk = '1' then
			case rec is
				when "01" =>
					q <= pc;
					en_mem <= '1';
				when "11" =>
					q <= alu_out;
					en_mem <= '0';
				when others =>
					en_mem <= 'Z';
					null;
			end case;
		end if;
	end process;
end behave;
