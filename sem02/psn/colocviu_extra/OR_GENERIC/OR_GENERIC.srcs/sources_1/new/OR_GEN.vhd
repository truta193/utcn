library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity OR_GENERIC is
    generic (n:integer);
    port (input: in std_logic_vector(n downto 1);
          output: out std_logic
          );
end OR_GENERIC;

architecture Flux of  OR_GENERIC is
begin
    process(input)
    variable result: std_logic;
    begin
        result := '0';
        for i in 1 to n loop
            result := result or input(i);
        end loop;
        output <= result;
    end process;
end Flux;