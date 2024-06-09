library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity alu is
    port(
        cin : in std_logic;
        alu_a, alu_b : in std_logic_vector(7 downto 0);
        alu_func : in std_logic_vector(2 downto 0);
        alu_out : out std_logic_vector(7 downto 0);
        c, z, v, s : out std_logic
    );
end alu;

architecture behave of alu is
    signal add_result : std_logic_vector(7 downto 0);
    signal add_carry : std_logic;
    signal sub_result : std_logic_vector(7 downto 0);
    signal sub_carry : std_logic;
    signal alu_a_complement : std_logic_vector(7 downto 0);
    signal complement_carry : std_logic;  
    signal shifted_b_left : std_logic_vector(7 downto 0);
    signal shifted_b_right : std_logic_vector(7 downto 0);

    component adder_8bit
        port (
            A, B : in std_logic_vector(7 downto 0);
            Cin : in std_logic;
            Sum : out std_logic_vector(7 downto 0);
            Cout : out std_logic
        );
    end component;
    
    component multiplier_8bit is
        port(
            A, B : in std_logic_vector(7 downto 0);
            product : out std_logic_vector(7 downto 0)
        );
    end component;

    signal one : std_logic_vector(7 downto 0) := "00000001";
    signal mult_product : std_logic_vector(7 downto 0);
    signal shifted_add_result : std_logic_vector(7 downto 0);
    signal shifted_add_carry : std_logic;

begin
    -- 加法器实例，用于alu_a的补码计算
    alu_b_complement_inst : adder_8bit
        port map(
            A => not alu_a,
            B => one,
            Cin => '0',
            Sum => alu_a_complement,
            Cout => complement_carry
        );

    -- 加法器实例，用于加法
    adder_inst : adder_8bit
        port map(
            A => alu_a,
            B => alu_b,
            Cin => cin,
            Sum => add_result,
            Cout => add_carry
        );

    -- 加法器实例，用于减法
    subtractor_inst : adder_8bit
        port map(
            A => alu_a_complement,
            B => alu_b,
            Cin => cin,
            Sum => sub_result,
            Cout => sub_carry
        );
    
    -- 乘法器实例
    multiplier_inst : multiplier_8bit
        port map(
            A => alu_a,
            B => alu_b,
            product => mult_product
        );

    -- 左移操作，用于逻辑左移
	shifted_b_left <= alu_b(6 downto 0) & "0";

    -- 右移操作，用于逻辑右移
	shifted_b_right <= "0" & alu_b(7 downto 1);

    process(alu_a, alu_b, cin, alu_func)
        variable temp2 : std_logic_vector(7 downto 0);
    begin
        case alu_func is
            when "000" =>  -- 加法
                temp2 := add_result;
            when "001" =>  -- 减法
                temp2 := sub_result;
            when "010" =>
                temp2 := alu_a and alu_b;
            when "011" =>
                temp2 := alu_a or alu_b;
            when "100" =>
                temp2 := alu_a xor alu_b;
            when "101" => -- 逻辑左移
                temp2 := shifted_b_left;
            when "110" => -- 逻辑右移
                temp2 := shifted_b_right;
            when "111" => -- 乘法
				temp2 := mult_product;
            when others =>
                temp2 := "00000000";
        end case;

        alu_out <= temp2;

        -- 置标志位Z，判断运算结果是否为0
        if temp2 = "00000000" then z <= '1';
        else z <= '0';
        end if;

        -- 置标志位S，判断运算结果的符号位（最高位）
        if temp2(7) = '1' then s <= '1';
        else s <= '0';
        end if;

        -- 置标志位V，判断运算结果是否溢出
        case alu_func is
            when "000" | "001" =>
                if (alu_a(7) = '1' and alu_b(7) = '1' and temp2(7) = '0') or
                   (alu_a(7) = '0' and alu_b(7) = '0' and temp2(7) = '1') then
                    v <= '1';
                else
                    v <= '0';
                end if;
            when others =>
                v <= '0';
        end case;

        -- 置标志位C，判断运算结果是否有进位
        case alu_func is
            when "000" => 
                c <= add_carry;
            when "001" =>
                c <= sub_carry;
            when "101" =>
                c <= alu_b(7);
            when "110" =>
                c <= alu_b(0);
            when others =>
                c <= '0';
        end case;
    end process;
end behave;
