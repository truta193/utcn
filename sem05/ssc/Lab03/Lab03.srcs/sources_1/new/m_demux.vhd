library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity m_demux is
    port (
        data_in1 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in2 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in3 : in STD_LOGIC_VECTOR(7 downto 0);
        data_in4 : in STD_LOGIC_VECTOR(7 downto 0);
        sel : in STD_LOGIC_VECTOR(1 downto 0);
        data_out : out STD_LOGIC_VECTOR(7 downto 0)
    );
end m_demux;

architecture Behavioral of m_demux is

begin

process(data_in1, data_in2, data_in3, data_in4, sel)
    begin
        data_out <= (others => '0');

        case sel is
            when "00" =>
                data_out <= data_in1;
            when "01" =>
                data_out <= data_in2;
            when "10" =>
                data_out <= data_in3;
            when "11" =>
                data_out <= data_in4;
            when others =>
                data_out <= (others => '0');
        end case;
    end process;

end Behavioral;
