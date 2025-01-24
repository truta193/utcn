library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_demux is
end tb_demux;

architecture Behavioral of tb_demux is

component m_demux is
    port (
        data_in1 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in2 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in3 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in4 : in STD_LOGIC_VECTOR(7 downto 0);
        sel : in STD_LOGIC_VECTOR(1 downto 0);
        data_out : out STD_LOGIC_VECTOR(7 downto 0)
    );
end component;


signal data_in1, data_in2, data_in3, data_in4 : STD_LOGIC_VECTOR(7 downto 0) := "00000000";
signal sel : STD_LOGIC_VECTOR(1 downto 0) := "00";
signal data_out : STD_LOGIC_VECTOR(7 downto 0) := "00000000";
constant T : time := 2ns;

begin
    mdmx: m_demux port map (
     data_in1 => data_in1, data_in2 => data_in2,
     data_in3 => data_in3, data_in4 => data_in4,
     sel => sel, data_out => data_out
    );
    

    
    process begin   
        data_in1 <= "00000001";
        data_in2 <= "00000010";    
        data_in3 <= "00000011";
        data_in4 <= "00000100";
        
        sel <= "00";
        wait for T;
    
        sel <= "01";
        wait for T;
    
        sel <= "10";
        wait for T;

        sel <= "11";
        wait for T;
    
        wait;
    end process;

end Behavioral;
