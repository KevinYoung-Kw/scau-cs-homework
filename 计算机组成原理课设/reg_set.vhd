library ieee;
use ieee.std_logic_1164.all;

entity reg_set is
    port(
        clk, reset, en: in std_logic;
        dest_reg, sour_reg: in std_logic_vector(1 downto 0);
        reg_sel: in std_logic_vector(2 downto 0);
        d: in std_logic_vector(7 downto 0);
        dr, sr, reg_out: out std_logic_vector(7 downto 0)
    );
end reg_set;

architecture behave of reg_set is
    signal reg_0, reg_1, reg_2, reg_3: std_logic_vector(7 downto 0);
    signal en_0, en_1, en_2, en_3: std_logic;
begin
    reg0: entity work.reg
        port map (
            d => d, clk => clk, reset => reset, en => en_0, q => reg_0
        );

    reg1: entity work.reg
        port map (
            d => d, clk => clk, reset => reset, en => en_1, q => reg_1
        );

    reg2: entity work.reg
        port map (
            d => d, clk => clk, reset => reset, en => en_2, q => reg_2
        );

    reg3: entity work.reg
        port map (
            d => d, clk => clk, reset => reset, en => en_3, q => reg_3
        );

    process(dest_reg, sour_reg, reg_sel, reg_0, reg_1, reg_2, reg_3, en)
        variable temp : std_logic_vector(3 downto 0);
    begin
        case dest_reg is
            when "00" =>
                dr <= reg_0;
                temp := "0001";
            when "01" =>
                dr <= reg_1;
                temp := "0010";
            when "10" =>
                dr <= reg_2;
                temp := "0100";
            when "11" =>
                dr <= reg_3;
                temp := "1000";
        end case;

        if en = '0' then
            temp := "0000";
            
        end if;
        en_0 <= temp(0);
        en_1 <= temp(1);
        en_2 <= temp(2);
        en_3 <= temp(3);

        case sour_reg is
            when "00" =>
                sr <= reg_0;
            when "01" =>
                sr <= reg_1;
            when "10" =>
                sr <= reg_2;
            when "11" =>
                sr <= reg_3;
        end case;

        case reg_sel is
            when "000" | "100" =>
                reg_out <= reg_0;
            when "001" | "101" =>
                reg_out <= reg_1;
            when "010" | "110" =>
                reg_out <= reg_2;
            when "011" | "111" =>
                reg_out <= reg_3;
        end case;
    end process;
end behave;
