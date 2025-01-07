library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity AND_GENERIC is
    generic (n:integer);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end AND_GENERIC;

architecture Flux of  AND_GENERIC is
signal check: std_logic_vector(n-1 downto 0)  := (others => '1');
begin
    output <= '1' when check = input else '0';
end Flux;