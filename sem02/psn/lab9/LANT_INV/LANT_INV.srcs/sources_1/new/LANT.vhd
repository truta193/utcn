----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/02/2023 10:59:56 AM
-- Design Name: 
-- Module Name: LANT - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity LANT is
    Generic (n : integer);
    Port (
        INPUT: in std_logic;
        OUTPUT: out std_logic
    );
end LANT;

architecture Behavioral of LANT is
    component INVERSOR is
        port (input : in std_logic; output : out std_logic);
    end component;
    --for all: INVERSOR use entity INVERSOR(COMP);
    signal P : std_logic_vector(1 to n+1);
    
begin
    INVERSOARE: for i in 1 to n generate
        INVERSOR_K: INVERSOR port map(P(i), P(i+1));
    end generate INVERSOARE;
    P(1) <= INPUT;
    OUTPUT <= P(N+1);
end Behavioral;


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity INVERSOR is
    port (input : in std_logic; output : out std_logic);
end INVERSOR;

architecture Flux of INVERSOR is
begin
    output <= not(input);
end Flux;
