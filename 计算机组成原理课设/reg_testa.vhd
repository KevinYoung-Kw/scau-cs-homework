library ieee;
use ieee.std_logic_1164.all;

entity reg_testa is
	port(
		clk, reset : in std_logic;
		input_a    : in std_logic_vector(2 downto 0);
		input_b    : in std_logic_vector(2 downto 0);
		input_c    : in std_logic_vector(2 downto 0);
		cin        : in std_logic;
		rec        : in std_logic_vector(1 downto 0);
		pc_en, reg_en, en_mem, wr : in std_logic;
	     q1           : out std_logic_vector(7 downto 0); -- ���������
		 q2           : out std_logic_vector(7 downto 0));
end reg_testa;

architecture behave of reg_testa is
begin
	process(clk, reset, input_a, input_b, input_c, cin, rec, pc_en, reg_en)
	variable temp1,temp2: std_logic_vector(7 downto 0);  -- �޸�Ϊ8λ����
	begin
		-- ƴ��8λ��temp����
		temp1 := cin & rec & pc_en & reg_en & en_mem & wr & input_a(2);
		temp2 := input_a(1) & input_a(0) & input_b & input_c;
		if reset = '0' then
			q1<="00000000";
			q2<="00000000"; -- 8λ����ֵ
		elsif clk'event and clk = '1' then
			q1 <= temp1;
			q2 <= temp2;
		end if;
	end process;
end behave;
