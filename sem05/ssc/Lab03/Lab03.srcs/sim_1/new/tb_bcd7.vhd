library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_bcd7 is
end tb_bcd7;

architecture Behavioral of tb_bcd7 is

component m_bcd7 is
    port (
        hex : in STD_LOGIC_VECTOR(3 downto 0);
        seg : out STD_LOGIC_VECTOR(6 downto 0)
    );
end component;

signal hex : STD_LOGIC_VECTOR(3 downto 0);
signal seg : STD_LOGIC_VECTOR(6 downto 0);

begin
    bcd7dec: m_bcd7 port map (
        hex => hex,
        seg => seg
    );
    
    process begin
        for i in 0 to 15 loop
            hex <= std_logic_vector(to_unsigned(i, 4));
            wait for 10 ns;
        end loop;

        wait;
    end process;

end Behavioral;
