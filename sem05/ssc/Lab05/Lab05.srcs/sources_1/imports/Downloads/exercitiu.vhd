----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/13/2024 09:41:50 PM
-- Design Name: 
-- Module Name: exercitiu - Behavioral
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
use IEEE.std_logic_arith.ALL;
USE IEEE.std_logic_unsigned.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity exercitiu is
Port(
    RST: in std_logic;
    CLK: in std_logic
);
end exercitiu;

architecture Behavioral of exercitiu is
--semnale
    --PC
    signal D: std_logic_vector(3 downto 0) :=(others => '0');
    signal Q: std_logic_vector(3 downto 0) :=(others => '0');
    --ROM
    signal ADR: std_logic_vector(3 downto 0) :=(others => '0');
    signal DO: std_logic_vector(3 downto 0) :=(others => '0');
    --MUXURI
    signal mux1_out: std_logic_vector(3 downto 0) :=(others => '0');
    signal mux2_out: std_logic_vector(3 downto 0) :=(others => '0');
    signal mux3_out: std_logic_vector(3 downto 0) :=(others => '0');
    signal mux4_out: std_logic_vector(3 downto 0) :=(others => '0');
    --SUMATOARE
    signal sum1_out: std_logic_vector(3 downto 0) :=(others => '0');
    signal sum2_out: std_logic_vector(3 downto 0) :=(others => '0');
    --REGISTRU
    signal RA1: std_logic_vector(3 downto 0) :=(others => '0');
    signal RA2: std_logic_vector(3 downto 0) :=(others => '0');
    signal WA: std_logic_vector(3 downto 0) :=(others => '0');
    signal WD: std_logic_vector(3 downto 0) :=(others => '0');
    signal RD1: std_logic_vector(3 downto 0) :=(others => '0');
    signal RD2: std_logic_vector(3 downto 0) :=(others => '0');
    --DCD
    signal RegDst: std_logic := '0';
    signal Jump: std_logic := '0';
    signal RegWr: std_logic := '0';
    signal SumToDst: std_logic := '0';
    signal SumSrc: std_logic := '0';
    signal IN_out: std_logic_vector(1 downto 0) := (others => '0');
    
    type ROM is array (0 to 15) of std_logic_vector(3 downto 0);
    signal rom_mem : ROM:= ( others => X"0");   
    
    type REG is array (0 to 15) of std_logic_vector(3 downto 0);
    signal reg_file : REG:= ( others => X"0");   
    
begin

    process(IN_out)
    begin
                   RegDst<='0';
                   Jump<='0';
                   RegWr<='0';  --poate sa lipseasca declararea asta, se pune doar in cazul in care se modifica doar unele
                   SumToDst<='0';
                   SumSrc<='0';
       case (IN_out) is
        when "00" => 
                   RegDst<='1';
                   Jump<='0';
                   RegWr<='1';
                   SumToDst<='1';
                   SumSrc<='1';
        when "01" => 
                   RegDst<='1';
                   Jump<='0';
                   RegWr<='0';
                   SumToDst<='0';
                   SumSrc<='1';
         when "10" => 
                   RegDst<='0';
                   Jump<='0';
                   RegWr<='0';
                   SumToDst<='1';
                   SumSrc<='0';
         when "11" => 
                   RegDst<='1';
                   Jump<='1';
                   RegWr<='0';
                   SumToDst<='0';
                   SumSrc<='1';
                   
        end case;
      end process;
      
      --sumator
      sum1_out <= "0010" + Q;
      sum2_out <= mux3_out + RD2;
      mux1_out <= sum1_out when Jump = '0' else DO;
      mux2_out <= DO when RegDst = '0' else Q;
      mux3_out <= RD1 when SumSrc = '0' else Q;
      mux4_out <= Q when SumToDst = '0' else sum2_out;
      
      IN_out <= RD2(1 downto 0); --sunt doar doi biti din RD2, nu conteaza daca e less sau most sign
      
      D <= mux1_OUT;
      process(CLK, RST)
        begin
        --observatie! SINCRON
        -- if CLK'event and CLK = '1' then
        -- if RST = '1' then --SINCRON
        
        --ASINCRON
       
        
        if RST = '1' then
             Q <= X"0";
        else if CLK = '1' and CLK'event then
            Q <= D;
         
        end if;
       end if;
       
     end process;
   
      ADR <= Q;
      --ROM
      DO <= rom_mem(conv_integer (ADR));
      
      RA1 <= DO;
      RA2 <= Q;
      WA <= mux2_out;
      WD <= mux4_out;
      --REG FILE
      process (CLK, RA1, RA2) 
        begin
            if CLK'event and CLK = '1' then
              if RegWr = '1' then 
                reg_file(conv_integer(WA)) <= WD;
              end if;
            end if;
             RD1 <= reg_file(conv_integer(RA1));
             RD2 <= reg_file(conv_integer(RA2));
      end process;
   

end Behavioral;
