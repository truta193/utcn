library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity XORR is
    port (
      A: in std_logic; 
      B: in std_logic;
      output: out std_logic
    );
end XORR;

architecture Behavioral of XORR is
component AND_GENERIC is
    generic (n:integer := 2);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end component;
component OR_GENERIC is
    generic (n:integer := 2);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end component;
component NOTT is
    port (input: in std_logic;
          output: out std_logic
          );
end component;
signal W1, W2, W3,W4, XY1, XY2: std_logic := '0';
signal BW1,AW2, XY: std_logic_vector(1 downto 0) := "00";
begin
    NOTA: NOTT port map(A, W1);
    BOTB: NOTT port map(B, W2);
    AW2 <= A & W2;
    NAANDB: AND_GENERIC port map (AW2, XY1);
    BW1 <= B & W1;
    NBANDA: AND_GENERIC port map (BW1, XY2);
    XY <= XY1 & XY2;
    FIN: OR_GENERIC port map(XY, output);
    
end Behavioral;







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







library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity OR_GENERIC is
    generic (n:integer);
    port (input: in std_logic_vector(n-1 downto 0);
          output: out std_logic
          );
end OR_GENERIC;

architecture Flux of  OR_GENERIC is
signal check: std_logic_vector(n-1 downto 0)  := (others => '1');
begin
    process(input)
    variable result: std_logic := '0';
    begin
        result := '0';
        for i in 0 to n-1 loop
            result := result or input(i);
        end loop;
        output <= result;
    end process;
end Flux;





library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity NOTT is
    port (input: in std_logic;
          output: out std_logic
          );
end NOTT;

architecture Flux of  NOTT is
begin
    output <= not input;
end Flux;