library ieee;
use ieee.std_logic_1164.all;

entity reg_test is
    port(
        clk, reset: in std_logic;
        input_0: in std_logic;
        input_1: in std_logic;
        input_2: in std_logic;
        input_3: in std_logic;
        input_4: in std_logic;
        input_5: in std_logic;
        input_6: in std_logic;
        input_7: in std_logic;
        q: out std_logic_vector(7 downto 0)
    );
end reg_test;

architecture behave of reg_test is
begin
    process(clk, reset)
        variable temp: std_logic_vector(7 downto 0);
    begin
        temp := input_7 & input_6 & input_5 & input_4 & input_3 & input_2 & input_1 & input_0;
        if reset = '1' then
            q <= "00000000";  -- 8 bits reset value
        elsif clk'event and clk = '1' then
            q <= temp;
        end if;
    end process;
end behave;
