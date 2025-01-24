library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity m_dec is
   port (
        a : in std_logic_vector(1 downto 0);
        y : out std_logic_vector(3 downto 0)
    );
end m_dec;

architecture Behavioral of m_dec is

begin
process (a)
    begin
        y <= (others => '0');
        
        case a is
            when "00" =>
                y(0) <= '1';
            when "01" =>
                y(1) <= '1';
            when "10" =>
                y(2) <= '1';
            when "11" =>
                y(3) <= '1';
            when others =>
                y <= (others => '0');
        end case;
    end process;

end Behavioral;