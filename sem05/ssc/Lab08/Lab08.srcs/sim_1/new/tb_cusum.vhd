library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_cusum is
end tb_cusum;

architecture Behavioral of tb_cusum is
    signal aclk : std_logic := '0';
    signal aresetn : std_logic := '0';

    signal s_axis_x_tvalid : std_logic := '0';
    signal s_axis_x_tready : std_logic;
    signal s_axis_x_tdata : std_logic_vector(31 downto 0) := (others => '0');
    signal s_axis_x_prev_tvalid : std_logic := '0';
    signal s_axis_x_prev_tready : std_logic;
    signal s_axis_x_prev_tdata : std_logic_vector(31 downto 0) := (others => '0');

    signal m_axis_result_tvalid : std_logic;
    signal m_axis_result_tready : std_logic := '0';
    signal m_axis_result_tdata : std_logic_vector(31 downto 0);

    constant clk_period : time := 10 ns;

begin
    dut: entity work.CUSUM_Top
        port map (
            aclk => aclk,
            aresetn => aresetn,
            s_axis_x_tvalid => s_axis_x_tvalid,
            s_axis_x_tready => s_axis_x_tready,
            s_axis_x_tdata => s_axis_x_tdata,
            s_axis_x_prev_tvalid => s_axis_x_prev_tvalid,
            s_axis_x_prev_tready => s_axis_x_prev_tready,
            s_axis_x_prev_tdata => s_axis_x_prev_tdata,
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
        aresetn <= '0';
        wait for clk_period * 2;
        aresetn <= '1';
        wait for clk_period * 2;

        s_axis_x_tdata <= std_logic_vector(to_signed(100, 32));
        s_axis_x_prev_tdata <= std_logic_vector(to_signed(100, 32));
        s_axis_x_tvalid <= '1';
        s_axis_x_prev_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        m_axis_result_tready <= '1';
        wait for clk_period;
        m_axis_result_tready <= '0';
        s_axis_x_tvalid <= '0';
        s_axis_x_prev_tvalid <= '0';

        s_axis_x_tdata <= std_logic_vector(to_signed(210, 32));
        s_axis_x_prev_tdata <= std_logic_vector(to_signed(200, 32));
        s_axis_x_tvalid <= '1';
        s_axis_x_prev_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        m_axis_result_tready <= '1';
        wait for clk_period;
        m_axis_result_tready <= '0';
        s_axis_x_tvalid <= '0';
        s_axis_x_prev_tvalid <= '0';

        s_axis_x_tdata <= std_logic_vector(to_signed(300, 32));
        s_axis_x_prev_tdata <= std_logic_vector(to_signed(100, 32));
        s_axis_x_tvalid <= '1';
        s_axis_x_prev_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        m_axis_result_tready <= '1';
        wait for clk_period;
        m_axis_result_tready <= '0';
        s_axis_x_tvalid <= '0';
        s_axis_x_prev_tvalid <= '0';

        wait;
    end process;

end Behavioral;
