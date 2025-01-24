library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity m_fa is
    port (
        a    : in  std_logic;
        b    : in  std_logic;
        cin  : in  std_logic;
        sum  : out std_logic;
        cout : out std_logic
    );
end m_fa;

architecture Behavioral of m_fa is
begin
    sum  <= (a xor b) xor cin;
    cout <= (a and b) or (cin and (a xor b));
end Behavioral;