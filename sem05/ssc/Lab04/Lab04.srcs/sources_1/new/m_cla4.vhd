library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity m_cla4 is
    port (
        a    : in std_logic_vector (3 downto 0);
        b    : in std_logic_vector (3 downto 0);
        cin  : in std_logic;
        sum  : out std_logic_vector (3 downto 0);
        cout : out std_logic
    );
end m_cla4;

architecture Behavioral of m_cla4 is
    signal p, g : std_logic_vector (3 downto 0);
    signal c    : std_logic_vector (4 downto 0);

begin
    g(0) <= a(0) and b(0);
    g(1) <= a(1) and b(1);
    g(2) <= a(2) and b(2);
    g(3) <= a(3) and b(3);

    p(0) <= a(0) or b(0);
    p(1) <= a(1) or b(1);
    p(2) <= a(2) or b(2);
    p(3) <= a(3) or b(3);

    c(0) <= cin;
    c(1) <= g(0) or (p(0) and c(0));
    c(2) <= g(1) or (p(1) and c(1));
    c(3) <= g(2) or (p(2) and c(2));
    cout <= g(3) or (p(3) and c(3));

    sum(0) <= a(0) xor b(0) xor c(0);
    sum(1) <= a(1) xor b(1) xor c(1);
    sum(2) <= a(2) xor b(2) xor c(2);
    sum(3) <= a(3) xor b(3) xor c(3);
end Behavioral;