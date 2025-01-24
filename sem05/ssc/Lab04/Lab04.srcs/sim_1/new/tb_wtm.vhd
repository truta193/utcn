library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity tb_wtm is
end tb_wtm;

architecture Behavioral of tb_wtm is
    signal a, b : std_logic_vector(3 downto 0);
    signal prod : std_logic_vector(7 downto 0);

    component m_wtm
        port (
            a : in  std_logic_vector(3 downto 0);
            b : in  std_logic_vector(3 downto 0);
            prod : out std_logic_vector(7 downto 0)
        );
    end component;

begin
    wtm: m_wtm port map (a => a, b => b, prod => prod);

    process begin
        a <= "0011";
        b <= "0010";
        wait for 10 ns;

        a <= "0111";
        b <= "0100";
        wait for 10 ns;

        a <= "1111";
        b <= "1111";
        wait for 10 ns;

        a <= "1000";
        b <= "1001";
        wait for 10 ns;

        a <= "0110";
        b <= "0110";
        wait for 10 ns;

        a <= "0000";
        b <= "0000";
        wait for 10 ns;

        a <= "0001";
        b <= "0001";
        wait for 10 ns;

        a <= "1111";
        b <= "0001";
        wait for 10 ns;

        a <= "0000";
        b <= "1111";
        wait for 10 ns;

        wait;
    end process;

end Behavioral;
