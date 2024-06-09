library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-- 指令存储器
entity rom is
    port (
        addr  :  in std_logic_vector(7 downto 0);
        en_mem:  in std_logic;
        instr : out std_logic_vector(7 downto 0)
    );
end rom;

architecture behavior of rom is
    type rom_type is array (255 downto 0) of std_logic_vector(7 downto 0);
    signal ROM : rom_type := (
        1 => "11110000",  -- MVRD
        2 => "00000011",  -- MVRD R0=3
        3 => "11110100",  -- MVRD
        4 => "00001010",  -- MVRD R1=10
        5 => "11111000",  -- MVRD
        6 => "00000100",  -- MVRD R2=4
        7 => "01101110",  -- MVRR R3=R2    (R3=4)
        8 => "00010100",  -- SUB  R1=R1-R0 (R1=7) 
        9 => "10010000",  -- SHL  R0=R0^2=(00000011)->(000000110)=6
        10 => "10101000", -- SHR  R2=R2/2=(00000100)->(000000010)=2 
        11 => "00001001", -- ADD  R2=R2+R1=2+7=9
        12 => "01111000", -- MULT R2=R2*R0=9*6=54	//R2=0
        
        13 => "00110110", -- CMP  R1, R2
        14 => "10110100", -- JRS  OFFSET=4, 当条件符合时，PC+2
        15 => "11111100", -- MVRD
        16 => "00001111", -- MVRD R3=15, 如果R3!=15，说明成功跳转
        
        17 => "00111001", -- CMP  R2, R1
        18 => "10110010", -- JRS  OFFSET=2, 当条件符合时，PC+2
        19 => "11111100", -- MVRD
        20 => "00001001", -- MVRD R3= 9, 如果R3!=9，说明成功跳转
					      -- 如果上述跳转均成功，则R3=4
					      
        21 => "10000100", -- INC  R1++, R1=8
        22 => "01101101", -- MVRR R3=R1
        23 => "01011110", -- OR   R3|R2
        24 => "01001011", -- XOR  R2^R3
        
        25 => "11100100", -- STRR [R1]<- R0
        26 => "11011001", -- LDRR  R2 <-[R1]
        
		27 => "11000000", -- JMPA 
        28 => "00010101", -- ADR = '25', 跳转到第25条指令形成循环
        
        others => (others => '0')
    );
begin
    process(addr, en_mem)
    begin
        if en_mem = '1' then
            instr <= ROM(conv_integer(addr));
        else
            instr <= (others => 'Z');
        end if;
    end process;
end behavior;
