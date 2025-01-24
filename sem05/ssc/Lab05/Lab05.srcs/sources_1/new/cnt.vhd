library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;

entity cnt is
    port (
        en: in std_logic;
        clk: in std_logic;
        ld: in std_logic;
        q: out std_logic_vector(2 downto 0)
    ); 
end cnt;

architecture Behavioral of cnt is
signal count : std_logic_vector(2 downto 0) := "000";
begin
    q <= count;

    process (clk)
 begin
       if rising_edge(clk) then
          if ld='1' then
             count <= (others => '0');
          elsif en='1' then
             count <= count + 1;
          end if;
       end if;
    end process;

end Behavioral;
