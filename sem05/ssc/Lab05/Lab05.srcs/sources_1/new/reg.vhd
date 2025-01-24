library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

ENTITY reg IS 
    PORT(
        d   : IN  STD_LOGIC_VECTOR(7 downto 0);
        ld  : IN  STD_LOGIC;
        clr : IN  STD_LOGIC;
        clk : IN  STD_LOGIC;
        q   : OUT STD_LOGIC_VECTOR(7 downto 0)
    );
END reg;

ARCHITECTURE Behavioral OF reg IS
    SIGNAL q_reg : STD_LOGIC_VECTOR(7 downto 0);
BEGIN
    process(clk, clr)
    begin
        if clr = '1' then
            q_reg <= (others => '0');
        elsif rising_edge(clk) then
            if ld = '1' then
                q_reg <= d;
            end if;
        end if;
    end process;

    q <= q_reg;
END Behavioral;

