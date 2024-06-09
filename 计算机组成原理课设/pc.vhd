library ieee;
use ieee.std_logic_1164.all;

entity pc is
	port(alu_out: in std_logic_vector(7 downto 0);
	     en: in std_logic;
	     clk, reset: in std_logic;
	     q: out std_logic_vector(7 downto 0));
end pc;

architecture behave of pc is
begin
	process(clk, reset)
	begin
		if reset = '0' then
			q <= "00000000";  -- 8 bits reset value
		elsif clk'event and clk = '1' then
			if en = '1' then
				q <= alu_out;
			end if;
		end if;
	end process;
end behave;
