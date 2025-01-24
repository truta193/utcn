library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity m_xor is
  Port ( a: in std_logic;
         b: in std_logic;
         outp: out std_logic);
end m_xor;

architecture Dataflow of m_xor is
    
begin
    outp <= a xor b;
end Dataflow;
