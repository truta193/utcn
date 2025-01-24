library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_subtractor is
end tb_subtractor;

architecture Behavioral of tb_subtractor is
    signal aclk               : std_logic := '0';
    signal s_axis_a_tvalid    : std_logic := '0';
    signal s_axis_a_tready    : std_logic;
    signal s_axis_a_tdata     : std_logic_vector(31 downto 0) := (others => '0');
    signal s_axis_b_tvalid    : std_logic := '0';
    signal s_axis_b_tready    : std_logic;
    signal s_axis_b_tdata     : std_logic_vector(31 downto 0) := (others => '0');
    signal m_axis_result_tvalid : std_logic;
    signal m_axis_result_tready : std_logic := '0';
    signal m_axis_result_tdata  : std_logic_vector(31 downto 0);

    constant clk_period : time := 10 ns;

begin
    addr: entity work.Subtractor
        port map (
            aclk => aclk,
            s_axis_a_tvalid => s_axis_a_tvalid,
            s_axis_a_tready => s_axis_a_tready,
            s_axis_a_tdata => s_axis_a_tdata,
            s_axis_b_tvalid => s_axis_b_tvalid,
            s_axis_b_tready => s_axis_b_tready,
            s_axis_b_tdata => s_axis_b_tdata,
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
        s_axis_a_tdata <= (others => '0');
        s_axis_b_tdata <= (others => '0');
        s_axis_a_tvalid <= '0';
        s_axis_b_tvalid <= '0';
        m_axis_result_tready <= '0';
        wait for clk_period * 2;

        s_axis_a_tdata <= std_logic_vector(to_signed(15, 32));
        s_axis_b_tdata <= std_logic_vector(to_signed(10, 32));
        s_axis_a_tvalid <= '1';
        s_axis_b_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        m_axis_result_tready <= '1';
        wait for clk_period;
        m_axis_result_tready <= '0';

        s_axis_a_tdata <= std_logic_vector(to_signed(-20, 32));
        s_axis_b_tdata <= std_logic_vector(to_signed(5, 32));
        s_axis_a_tvalid <= '1';
        s_axis_b_tvalid <= '1';
        m_axis_result_tready <= '1';

        wait until m_axis_result_tvalid = '1';

        m_axis_result_tready <= '1';
        wait for clk_period;
        m_axis_result_tready <= '0';

        wait;
    end process;

end Behavioral;
