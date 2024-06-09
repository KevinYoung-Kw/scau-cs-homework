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
    -- �ӷ���ʵ��������alu_a�Ĳ������
    alu_b_complement_inst : adder_8bit
        port map(
            A => not alu_a,
            B => one,
            Cin => '0',
            Sum => alu_a_complement,
            Cout => complement_carry
        );

    -- �ӷ���ʵ�������ڼӷ�
    adder_inst : adder_8bit
        port map(
            A => alu_a,
            B => alu_b,
            Cin => cin,
            Sum => add_result,
            Cout => add_carry
        );

    -- �ӷ���ʵ�������ڼ���
    subtractor_inst : adder_8bit
        port map(
            A => alu_a_complement,
            B => alu_b,
            Cin => cin,
            Sum => sub_result,
            Cout => sub_carry
        );
    
    -- �˷���ʵ��
    multiplier_inst : multiplier_8bit
        port map(
            A => alu_a,
            B => alu_b,
            product => mult_product
        );

    -- ���Ʋ����������߼�����
	shifted_b_left <= alu_b(6 downto 0) & "0";

    -- ���Ʋ����������߼�����
	shifted_b_right <= "0" & alu_b(7 downto 1);

    process(alu_a, alu_b, cin, alu_func)
        variable temp2 : std_logic_vector(7 downto 0);
    begin
        case alu_func is
            when "000" =>  -- �ӷ�
                temp2 := add_result;
            when "001" =>  -- ����
                temp2 := sub_result;
            when "010" =>
                temp2 := alu_a and alu_b;
            when "011" =>
                temp2 := alu_a or alu_b;
            when "100" =>
                temp2 := alu_a xor alu_b;
            when "101" => -- �߼�����
                temp2 := shifted_b_left;
            when "110" => -- �߼�����
                temp2 := shifted_b_right;
            when "111" => -- �˷�
				temp2 := mult_product;
            when others =>
                temp2 := "00000000";
        end case;

        alu_out <= temp2;

        -- �ñ�־λZ���ж��������Ƿ�Ϊ0
        if temp2 = "00000000" then z <= '1';
        else z <= '0';
        end if;

        -- �ñ�־λS���ж��������ķ���λ�����λ��
        if temp2(7) = '1' then s <= '1';
        else s <= '0';
        end if;

        -- �ñ�־λV���ж��������Ƿ����
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

        -- �ñ�־λC���ж��������Ƿ��н�λ
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
