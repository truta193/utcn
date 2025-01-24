library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_arith.ALL;

entity m_wtm is
    port ( 
       a : in  std_logic_vector (3 downto 0);
       b : in  std_logic_vector (3 downto 0);
       prod : out  std_logic_vector (7 downto 0)
    );
end m_wtm;

architecture Behavioral of m_wtm is

component m_fa is
    port (
        a    : in  std_logic;
        b    : in  std_logic;
        cin  : in  std_logic;
        sum  : out std_logic;
        cout : out std_logic
    );
end component;

signal s11, s12, s13, s14, s15, s22, s23, s24, s25, s26, s32, s33, s34, s35, s36, s37 : std_logic;
signal c11, c12, c13, c14, c15, c22, c23, c24, c25, c26, c32, c33, c34, c35, c36, c37 : std_logic;
signal p0, p1, p2, p3 : std_logic_vector(6 downto 0);

begin
    process(a,b) begin
        for i in 0 to 3 loop
            p0(i) <= a(i) and b(0);
            p1(i) <= a(i) and b(1);
            p2(i) <= a(i) and b(2);
            p3(i) <= a(i) and b(3);
        end loop;       
    end process;
        
    prod(0) <= p0(0);
    prod(1) <= s11;
    prod(2) <= s22;
    prod(3) <= s32;
    prod(4) <= s34;
    prod(5) <= s35;
    prod(6) <= s36;
    prod(7) <= s37;
    
    fa11 : m_fa port map(p0(1), p1(0), '0', s11, c11);
    fa12 : m_fa port map(p0(2),p1(1),p2(0),s12,c12);
    fa13 : m_fa port map(p0(3),p1(2),p2(1),s13,c13);
    fa14 : m_fa port map(p1(3),p2(2),p3(1),s14,c14);
    fa15 : m_fa port map(p2(3),p3(2),'0',s15,c15);
    
    fa22 : m_fa port map(c11,s12, '0', s22,c22);
    fa23 : m_fa port map(p3(0),c12,s13,s23,c23);
    fa24 : m_fa port map(c13,c32,s14,s24,c24);
    fa25 : m_fa port map(c14,c24,s15,s25,c25);
    fa26 : m_fa port map(c15,c25,p3(3),s26,c26);
    
    fa32 : m_fa port map(c22,s23,'0',s32,c32);
    fa34 : m_fa port map(c23,s24,'0',s34,c34);
    fa35 : m_fa port map(c34,s25,'0',s35,c35);
    fa36 : m_fa port map(c35,s26,'0',s36,c36);
    fa37 : m_fa port map(c36,c26,'0',s37,c37);
    
end Behavioral;