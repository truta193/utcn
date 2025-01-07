library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.math_real.all;

entity MUX_GEN is
    generic (n:integer := 4);
    port (
        input: in std_logic_vector(n-1 downto 0);
        sel: in std_logic_vector(integer(ceil(log2(real(n))))-1 downto 0);
        outp: out std_logic
    );
end MUX_GEN;

architecture Behavioral of MUX_GEN is

begin
    outp <= input(conv_integer(sel));
end Behavioral;
