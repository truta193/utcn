library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ThresholdComparator is
    Port (
        aclk : IN STD_LOGIC;
        s_axis_g_plus_tvalid : IN STD_LOGIC;
        s_axis_g_plus_tready : OUT STD_LOGIC;
        s_axis_g_plus_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        s_axis_g_minus_tvalid : IN STD_LOGIC;
        s_axis_g_minus_tready : OUT STD_LOGIC;
        s_axis_g_minus_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        s_axis_threshold_tvalid : IN STD_LOGIC;
        s_axis_threshold_tready : OUT STD_LOGIC;
        s_axis_threshold_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        m_axis_result_tvalid : OUT STD_LOGIC;
        m_axis_result_tready : IN STD_LOGIC;
        m_axis_result_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
end ThresholdComparator;

architecture Behavioral of ThresholdComparator is
    type state_type is (S_READ, S_WRITE);
    signal state : state_type := S_READ;

    signal res_valid : STD_LOGIC := '0';
    signal result : STD_LOGIC_VECTOR (31 DOWNTO 0) := (others => '0'); -- Label (1 = True, 0 = False)
    signal g_plus, g_minus, threshold : STD_LOGIC_VECTOR (31 DOWNTO 0) := (others => '0');

    signal internal_ready, external_ready, inputs_valid : STD_LOGIC := '0';
begin
    s_axis_g_plus_tready <= external_ready;
    s_axis_g_minus_tready <= external_ready;
    s_axis_threshold_tready <= external_ready;

    internal_ready <= '1' when state = S_READ else '0';
    inputs_valid <= s_axis_g_plus_tvalid and s_axis_g_minus_tvalid and s_axis_threshold_tvalid;
    external_ready <= internal_ready and inputs_valid;

    m_axis_result_tvalid <= '1' when state = S_WRITE else '0';
    m_axis_result_tdata <= result;

    process(aclk)
    begin
        if rising_edge(aclk) then
            case state is
                when S_READ =>
                    if external_ready = '1' and inputs_valid = '1' then
                        g_plus <= s_axis_g_plus_tdata;
                        g_minus <= s_axis_g_minus_tdata;
                        threshold <= s_axis_threshold_tdata;

                        if signed(g_plus) > signed(threshold) or signed(g_minus) > signed(threshold) then
                            result <= std_logic_vector(to_signed(1, 32)); 
                            g_plus <= (others => '0');
                            g_minus <= (others => '0');
                        else
                            result <= std_logic_vector(to_signed(0, 32));
                        end if;

                        state <= S_WRITE;
                    end if;

                when S_WRITE =>
                    if m_axis_result_tready = '1' then
                        state <= S_READ;
                    end if;
            end case;
        end if;
    end process;

end Behavioral;
