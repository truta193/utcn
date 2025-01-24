library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_cnt is
end tb_cnt;

architecture Behavioral of tb_cnt is

component m_cnt is
port (
    clk: in std_logic;
    count: out std_logic_vector (2 downto 0)
);
end component;

constant T : time := 4ns;
signal clk : std_logic := '0';
signal count : std_logic_vector (2 downto 0) := (others => '0');

begin
    clk <= not clk after T / 2;

    cntr : m_cnt port map (
        clk => clk, count => count
    );
    
    process begin
        wait for T;
        wait for T;
        wait for T;
        wait for T;
        wait for T;
        wait for T;
        wait for T;
        wait for T;
        wait;
    end process;

end Behavioral;
