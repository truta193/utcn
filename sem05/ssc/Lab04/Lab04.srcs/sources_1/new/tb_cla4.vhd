library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_cla4 is
end tb_cla4;

architecture Behavioral of tb_cla4 is
    component m_cla4
        port (
            a : in std_logic_vector (3 downto 0);
            b : in std_logic_vector (3 downto 0);
            cin : in std_logic;
            sum : out std_logic_vector (3 downto 0);
            cout : out std_logic
        );
    end component;

    signal a, b : std_logic_vector(3 downto 0);
    signal cin : std_logic;
    signal sum : std_logic_vector(3 downto 0);
    signal cout : std_logic;

begin
    cla: m_cla4 port map (
        a => a,
        b => b,
        cin => cin,
        sum => sum,
        cout => cout
    );

    process begin
        a <= "0001"; b <= "0010"; cin <= '0';
        wait for 10 ns;

        a <= "0011"; b <= "0101"; cin <= '0';
        wait for 10 ns;

        a <= "1111"; b <= "1111"; cin <= '0';
        wait for 10 ns;

        a <= "1010"; b <= "0101"; cin <= '1';
        wait for 10 ns;
        
        a <= "0000"; b <= "0000"; cin <= '0';
        wait;
    end process;

end Behavioral;