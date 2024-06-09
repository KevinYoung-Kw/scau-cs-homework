library ieee;
use ieee.std_logic_1164.all;

entity reg_out is
    port(
        ir, pc, reg_in: in std_logic_vector(7 downto 0);
        offset, alu_a, alu_b: in std_logic_vector(7 downto 0);
        alu_out, reg_testa1, reg_testa2: in std_logic_vector(7 downto 0);
        reg_sel: in std_logic_vector(2 downto 0);
        sel: in std_logic_vector(1 downto 0);
        reg_data1:            out std_logic_vector(7 downto 0);
		reg_data2:            out std_logic_vector(7 downto 0));
end reg_out;

architecture behave of reg_out is
begin
    process(ir, pc, reg_in, sel, reg_sel, offset, alu_a, alu_b, alu_out, reg_testa1, reg_testa2)
    begin
		reg_data1 <= "00000000";
        case sel is
            when "00" =>
                reg_data2 <= reg_in;
            when "01" =>
                case reg_sel is
                    when "000" =>
                        reg_data2 <= offset;
                    when "001" =>
                        reg_data2 <= alu_a;
                    when "010" =>
                        reg_data2 <= alu_b;
                    when "011" =>
                        reg_data2 <= alu_out;
                    when "100" =>
						reg_data1 <= reg_testa1;
						reg_data2 <= reg_testa2;
                    when others =>
                        reg_data2 <= "00000000";
                end case;
            when "11" =>
                case reg_sel is
                    when "110" =>
                        reg_data2 <= pc;
                    when "111" =>
                        reg_data2 <= ir;
                    when others =>
                        reg_data2 <= "00000000";
                end case;
            when others =>
                reg_data2 <= "00000000";
        end case;
    end process;
end behave;
