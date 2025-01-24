library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_dec is
end tb_dec;

architecture Behavioral of tb_dec is

component  m_dec is
   port (
        a : in std_logic_vector(1 downto 0);
        y : out std_logic_vector(3 downto 0)
    );
end component;

constant T : time := 4ns;
signal a : std_logic_vector(1 downto 0);
signal y : std_logic_vector(3 downto 0);

begin
    dcdr: m_dec port map (
        a => a, y => y
    );
    
    process begin
        a <= "00";
        wait for T;
        
        a <= "01";
        wait for T;
        
        a <= "10";
        wait for T;
        
        a <= "11";
        wait for T;

        wait;
    end process;
end Behavioral;
