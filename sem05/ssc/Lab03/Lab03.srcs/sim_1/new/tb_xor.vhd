library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_xor is
end tb_xor;

architecture Behavioral of tb_xor is

component m_xor is
  Port ( a: in std_logic;
         b: in std_logic;
         outp: out std_logic);
end component;

signal a, b, outp : std_logic := '0';
constant T : time := 4ns;

begin
    -- Instantiate the XOR component
    mtb_xor: m_xor port map (
        a => a,
        b => b,
        outp => outp
    );

    process
    begin
        wait for T; 
        a <= '1'; 
        b <= '0';
        
        wait for T;
        a <= '0'; 
        b <= '1'; 
        
        wait for T;
        a <= '1';
        b <= '1'; 
        
        wait for 3*T;
        
        wait;
    end process;

end Behavioral;