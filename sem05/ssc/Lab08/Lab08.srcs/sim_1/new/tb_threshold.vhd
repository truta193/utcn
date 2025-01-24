library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_threshold is
end tb_threshold;

architecture Behavioral of tb_threshold is
    signal aclk                  : std_logic := '0';
    signal s_axis_g_plus_tvalid  : std_logic := '0';
    signal s_axis_g_plus_tready  : std_logic;
    signal s_axis_g_plus_tdata   : std_logic_vector(31 downto 0) := (others => '0');
    signal s_axis_g_minus_tvalid : std_logic := '0';
    signal s_axis_g_minus_tready : std_logic;
    signal s_axis_g_minus_tdata  : std_logic_vector(31 downto 0) := (others => '0');
    signal s_axis_threshold_tvalid : std_logic := '0';
    signal s_axis_threshold_tready : std_logic;
    signal s_axis_threshold_tdata  : std_logic_vector(31 downto 0) := (others => '0');
    signal m_axis_result_tvalid  : std_logic;
    signal m_axis_result_tready  : std_logic := '0';
    signal m_axis_result_tdata   : std_logic_vector(31 downto 0);

    constant clk_period : time := 10 ns;

begin
    comparator: entity work.ThresholdComparator
        port map (
            aclk => aclk,
            s_axis_g_plus_tvalid => s_axis_g_plus_tvalid,
            s_axis_g_plus_tready => s_axis_g_plus_tready,
            s_axis_g_plus_tdata => s_axis_g_plus_tdata,
            s_axis_g_minus_tvalid => s_axis_g_minus_tvalid,
            s_axis_g_minus_tready => s_axis_g_minus_tready,
            s_axis_g_minus_tdata => s_axis_g_minus_tdata,
            s_axis_threshold_tvalid => s_axis_threshold_tvalid,
            s_axis_threshold_tready => s_axis_threshold_tready,
            s_axis_threshold_tdata => s_axis_threshold_tdata,
            m_axis_result_tvalid => m_axis_result_tvalid,
            m_axis_result_tready => m_axis_result_tready,
            m_axis_result_tdata => m_axis_result_tdata
        );

    clk_process: process
    begin
        aclk <= '1';
        wait for clk_period / 2;
        aclk <= '0';
        wait for clk_period / 2;
    end process;

    process
    begin
        s_axis_g_plus_tdata <= (others => '0');
        s_axis_g_minus_tdata <= (others => '0');
        s_axis_threshold_tdata <= (others => '0');
        s_axis_g_plus_tvalid <= '0';
        s_axis_g_minus_tvalid <= '0';
        s_axis_threshold_tvalid <= '0';
        m_axis_result_tready <= '0';
        wait for clk_period * 2;

        s_axis_g_plus_tdata <= std_logic_vector(to_signed(60, 32));
        s_axis_g_minus_tdata <= std_logic_vector(to_signed(40, 32));
        s_axis_threshold_tdata <= std_logic_vector(to_signed(50, 32));
        s_axis_g_plus_tvalid <= '1';
        s_axis_g_minus_tvalid <= '1';
        s_axis_threshold_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        assert signed(m_axis_result_tdata) = 1 report "Test case 1 failed: Expected label 1 (True)" severity error;

        m_axis_result_tready <= '0';
        wait for clk_period;

        s_axis_g_plus_tdata <= std_logic_vector(to_signed(30, 32));
        s_axis_g_minus_tdata <= std_logic_vector(to_signed(40, 32));
        s_axis_threshold_tdata <= std_logic_vector(to_signed(50, 32));
        s_axis_g_plus_tvalid <= '1';
        s_axis_g_minus_tvalid <= '1';
        s_axis_threshold_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        assert signed(m_axis_result_tdata) = 0 report "Test case 2 failed: Expected label 0 (False)" severity error;

        m_axis_result_tready <= '0';
        wait for clk_period;

        s_axis_g_plus_tdata <= std_logic_vector(to_signed(40, 32));
        s_axis_g_minus_tdata <= std_logic_vector(to_signed(60, 32));
        s_axis_threshold_tdata <= std_logic_vector(to_signed(50, 32));
        s_axis_g_plus_tvalid <= '1';
        s_axis_g_minus_tvalid <= '1';
        s_axis_threshold_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        assert signed(m_axis_result_tdata) = 1 report "Test case 3 failed: Expected label 1 (True)" severity error;

        m_axis_result_tready <= '0';
        wait for clk_period;

        wait;
    end process;

end Behavioral;
