library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity multiplier_8bit is
    port(
        A, B : in std_logic_vector(7 downto 0);
        product : out std_logic_vector(7 downto 0)
    );
end multiplier_8bit;

architecture behave of multiplier_8bit is
    signal temp_product : std_logic_vector(15 downto 0);
begin
    process(A, B)
    begin
        temp_product <= (others => '0');  -- 初始化乘积为全零
        for i in 0 to 7 loop
            if B(i) = '1' then
                temp_product(15 downto 8) <= temp_product(15 downto 8) + A;
            end if;
            temp_product <= temp_product(14 downto 0) & '0';  -- 左移一位
        end loop;
        product <= temp_product(7 downto 0);  -- 输出结果的低 8 位
    end process;
end behave;