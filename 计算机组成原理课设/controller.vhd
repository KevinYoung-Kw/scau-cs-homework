library ieee;
use ieee.std_logic_1164.all;

entity controller is  --实体描述
port( timer:                  in std_logic_vector(2 downto 0);  --节拍
     instruction:             in std_logic_vector(7 downto 0);  --指令内容
     c,z,v,s:                 in std_logic;  --标志位
   dest_reg,sour_reg:       out std_logic_vector(1 downto 0);  --目的和源寄存器的选择信号
     offset:                 out std_logic_vector(3 downto 0);  --偏移地址
     sst,sci,rec:             out std_logic_vector(1 downto 0); --输出各个控制信号
     alu_func,alu_in_sel:     out std_logic_vector(2 downto 0);
     en_reg,en_pc,wr:        out std_logic);
end controller;

architecture behave of controller is
begin
	process(timer,instruction,c,z,v,s)
	variable temp1,temp2 : std_logic_vector(3 downto 0) ;
	variable temp3,temp4 : std_logic_vector(1 downto 0) ;
	variable alu_out_sel: std_logic_vector(1 downto 0);
	begin
	    for I in 3 downto 0 loop
		    temp1(I):=instruction(I+4);  --暂存指令高4位
		    temp2(I):=instruction(I);  --暂存指令低4位
	    end loop;
	    for I in 1 downto 0 loop
		    temp3(I):=instruction(I+2);  --暂存低4位
		    temp4(I):=instruction(I);  --暂存低4位
	    end loop;
		case timer is
		    when "100"=>  --初始状态
				dest_reg<="00";
				sour_reg<="00";
				offset<="0000";
				sci<="00";
				sst<="11";
				alu_out_sel:="00";
				alu_in_sel<="000";
				alu_func<="000";
				wr<='1';
				rec<="00";
			when "000"=>  --读取指令第一拍
				dest_reg<="00";
				sour_reg<="00";
				offset<="0000";
				sci<="01";
				sst<="11";
				alu_out_sel:="10";
				alu_in_sel<="100";
				alu_func<="000";
				wr<='1';
				rec<="01";
			when "001"=>  --读内存，放到指令寄存器
				dest_reg<="00";
				sour_reg<="00";
				offset<="0000";
				sci<="00";
				sst<="11";
				alu_out_sel:="00";
				alu_in_sel<="000";
				alu_func<="000";
				wr<='1';
				rec<="10";
			when "011"=>  --A组指令
				wr<='1';
				case temp1 is
				when "0000"=>  --ADD
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="000";
					when "0001"=>  --SUB
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="001";
					when "0010"=>  --AND
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="010";
					when "0011"=>  --CMP
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="00";
					alu_in_sel<="000";
					alu_func<="001";
					when "0100"=>  --XOR
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="100";
					when "0101"=>  --OR
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="011";
					when "0110"=>  --MVRR
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="11";
					alu_out_sel:="01";
					alu_in_sel<="001";
					alu_func<="000";
					when "0111"=>  --MULT
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="000";
					alu_func<="111";
					when "1000"=>  --INC
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="01";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="010";
					alu_func<="000";
					when "1001"=>  --SHL
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="010";
					alu_func<="101";
					when "1010"=>  --SHR
					dest_reg<=temp3;
					sour_reg<=temp4;
					offset<="0000";
					sci<="00";
					sst<="00";
					alu_out_sel:="01";
					alu_in_sel<="010";
					alu_func<="110";
					when "1011"=>  --JRS
					dest_reg<="00";
					sour_reg<="00";
					offset<=temp2;
					sci<="00";
					sst<="11";
					alu_out_sel:=s&"0";
					alu_in_sel<="011";
					alu_func<="000";				
					when others=>
					null;
				end case;
			when "101"=>  --B组指令
				alu_func<="000";
				wr<='1';
				sst<="11";
				dest_reg<=temp3;
				sour_reg<=temp4;
				offset<="0000";
				case temp1 is
					when "1100" | "1111"=>  --读取双字指令的后一半
					sci<="01";
					alu_out_sel:="10";
					alu_in_sel<="100";
					rec<="01";
					when "1101"=>  --目的地址送地址寄存器
					sci<="00";
					alu_out_sel:="00";
					alu_in_sel<="001";
					rec<="11";
					when "1110"=>	--[DR]<-SR
					sci<="00";
					alu_out_sel:="00";
					alu_in_sel<="010";
					rec<="11";
					when others=>
					null;
				end case;
			when "111"=>  --读写内存
				dest_reg<=temp3;
				sour_reg<=temp4;
				offset<="0000";
				sci<="00";
				sst<="11";
				alu_func<="000";
				rec<="00";
				case temp1 is
					when "1101" | "1111"=>	
					alu_out_sel:="01";
					alu_in_sel<="101";
					wr<='1';
					when "1100"=> 
					alu_out_sel:="10";
					alu_in_sel<="101";
					wr<='1';
					when "1110"=>
					alu_out_sel:="00";
					alu_in_sel<="001";
					wr<='0';
					when others=>
					null;
				end case;
			when others=>
			null;
		end case;
		en_reg<=alu_out_sel(0);
		en_pc<=alu_out_sel(1);
	end process;
end behave;

