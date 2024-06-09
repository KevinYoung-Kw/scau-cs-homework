library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity adder_8bit is
    port(
        A, B : in std_logic_vector(7 downto 0);
        Cin  : in std_logic;
        Sum  : out std_logic_vector(7 downto 0);
        Cout : out std_logic
    );
end adder_8bit;

architecture behave of adder_8bit is
    signal carry : std_logic_vector(8 downto 0);
begin
    carry(0) <= Cin;
    gen_adder : for i in 0 to 7 generate
    begin
        Sum(i) <= A(i) xor B(i) xor carry(i);
        carry(i+1) <= (A(i) and B(i)) or (A(i) and carry(i)) or (B(i) and carry(i));
    end generate;
    Cout <= carry(8);
end behave;