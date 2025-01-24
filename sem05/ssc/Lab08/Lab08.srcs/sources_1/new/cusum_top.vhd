library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity CUSUM_Top is
    Port (
        aclk : IN STD_LOGIC; 
        aresetn : IN STD_LOGIC;
        s_axis_x_tvalid : IN STD_LOGIC;
        s_axis_x_tready : OUT STD_LOGIC;
        s_axis_x_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        s_axis_x_prev_tvalid : IN STD_LOGIC;
        s_axis_x_prev_tready : OUT STD_LOGIC;
        s_axis_x_prev_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        m_axis_result_tvalid : OUT STD_LOGIC;
        m_axis_result_tready : IN STD_LOGIC;
        m_axis_result_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
end CUSUM_Top;

architecture Behavioral of CUSUM_Top is
COMPONENT fifo
  PORT (
    s_axis_aresetn : IN STD_LOGIC;
    s_axis_aclk : IN STD_LOGIC;
    s_axis_tvalid : IN STD_LOGIC;
    s_axis_tready : OUT STD_LOGIC;
    s_axis_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axis_tvalid : OUT STD_LOGIC;
    m_axis_tready : IN STD_LOGIC;
    m_axis_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0) 
  );
END COMPONENT;
COMPONENT axis_broadcaster_0
  PORT (
    aclk : IN STD_LOGIC;
    aresetn : IN STD_LOGIC;
    s_axis_tvalid : IN STD_LOGIC;
    s_axis_tready : OUT STD_LOGIC;
    s_axis_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axis_tvalid : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axis_tready : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axis_tdata : OUT STD_LOGIC_VECTOR(63 DOWNTO 0) 
  );
END COMPONENT;
    -- FIFO signals
    
    signal thresh_g_plus_tdata : std_logic_vector(31 downto 0);
    signal thresh_g_plus_tready : std_logic;
    signal thresh_g_plus_tvalid : std_logic;
    signal thresh_g_minus_tdata : std_logic_vector(31 downto 0);
    signal thresh_g_minus_tready : std_logic;
    signal thresh_g_minus_tvalid : std_logic;
    
    signal fifo_g_plus_tdata : std_logic_vector(31 downto 0);
    signal fifo_g_plus_tready : std_logic;
    signal fifo_g_plus_tvalid : std_logic;
    signal fifo_g_minus_tdata : std_logic_vector(31 downto 0);
    signal fifo_g_minus_tready : std_logic;
    signal fifo_g_minus_tvalid : std_logic;
    
    signal fifo_x_tvalid, fifo_x_tready : std_logic;
    signal fifo_x_tdata : std_logic_vector(31 downto 0);

    signal fifo_x_prev_tvalid, fifo_x_prev_tready : std_logic;
    signal fifo_x_prev_tdata : std_logic_vector(31 downto 0);

    signal subtractor_out, subtractor_fifo_out : std_logic_vector(31 downto 0);
    signal subtractor_fifo_valid, subtractor_fifo_ready : std_logic;

    signal broadcaster_tvalid : std_logic;
    signal broadcaster_tready : std_logic;
    signal broadcaster_tdata : std_logic_vector(31 downto 0);
    
    signal broadcaster_out_tvalid :  STD_LOGIC_VECTOR(1 DOWNTO 0);
    signal broadcaster_out_tready :  STD_LOGIC_VECTOR(1 DOWNTO 0);
    signal broadcaster_out_tdata :  STD_LOGIC_VECTOR(63 DOWNTO 0);
    
    signal adder_out_tvalid :  STD_LOGIC;
    signal adder_out_tready :  STD_LOGIC;
    signal adder_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    signal sub1_out_tvalid :  STD_LOGIC;
    signal sub1_out_tready :  STD_LOGIC;
    signal sub1_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal fifo_sub1_out_tvalid :  STD_LOGIC;
    signal fifo_sub1_out_tready :  STD_LOGIC;
    signal fifo_sub1_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    signal fifo_adder_out_tvalid :  STD_LOGIC;
    signal fifo_adder_out_tready :  STD_LOGIC;
    signal fifo_adder_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal drift_out_tvalid :  STD_LOGIC;
    signal drift_out_tready :  STD_LOGIC;
    signal drift_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal drift_sub_tvalid :  STD_LOGIC;
    signal drift_sub_tready :  STD_LOGIC;
    signal drift_sub_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal max_out_tvalid :  STD_LOGIC;
    signal max_out_tready :  STD_LOGIC;
    signal max_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal max_sub_tvalid :  STD_LOGIC;
    signal max_sub_tready :  STD_LOGIC;
    signal max_sub_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal fifo_max_out_tvalid :  STD_LOGIC;
    signal fifo_max_out_tready :  STD_LOGIC;
    signal fifo_max_out_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal fifo_max_sub_tvalid :  STD_LOGIC;
    signal fifo_max_sub_tready :  STD_LOGIC;
    signal fifo_max_sub_tdata :  STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    
    
    constant drift : std_logic_vector(31 downto 0) := std_logic_vector(to_signed(50, 32)); -- Drift value
    constant threshold : std_logic_vector(31 downto 0) := std_logic_vector(to_signed(200, 32)); -- Threshold value
begin

   fifo_g_plus_t_1: fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => fifo_max_out_tvalid,
            s_axis_tready  => fifo_max_out_tready,
            s_axis_tdata   => fifo_max_out_tdata,
            m_axis_tvalid  => fifo_g_plus_tvalid,
            m_axis_tready  => fifo_g_plus_tready,
            m_axis_tdata   => fifo_g_plus_tdata
        );
        
    fifo_g_minus_t_1: fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => fifo_max_sub_tvalid,
            s_axis_tready  => fifo_max_sub_tready,
            s_axis_tdata   => fifo_max_sub_tdata,
            m_axis_tvalid  => fifo_g_minus_tvalid,
            m_axis_tready  => fifo_g_minus_tready,
            m_axis_tdata   => fifo_g_minus_tdata
        );

-- FIFO for x_t
    fifo_x_t_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => s_axis_x_tvalid,
            s_axis_tready  => s_axis_x_tready,
            s_axis_tdata   => s_axis_x_tdata,
            m_axis_tvalid  => fifo_x_tvalid,
            m_axis_tready  => fifo_x_tready,
            m_axis_tdata   => fifo_x_tdata
        );

    -- FIFO for x_t-1
    fifo_x_prev_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => s_axis_x_prev_tvalid,
            s_axis_tready  => s_axis_x_prev_tready,
            s_axis_tdata   => s_axis_x_prev_tdata,
            m_axis_tvalid  => fifo_x_prev_tvalid,
            m_axis_tready  => fifo_x_prev_tready,
            m_axis_tdata   => fifo_x_prev_tdata
        );

    -- Subtractor instance
    subtractor_inst : entity work.Subtractor
        port map (
            aclk => aclk,
            s_axis_a_tvalid => fifo_x_tvalid,
            s_axis_a_tready => fifo_x_tready,
            s_axis_a_tdata => fifo_x_tdata, -- x_t
            s_axis_b_tvalid => fifo_x_prev_tvalid,
            s_axis_b_tready => fifo_x_prev_tready,
            s_axis_b_tdata => fifo_x_prev_tdata, -- x_t-1
            m_axis_result_tvalid => subtractor_fifo_valid,
            m_axis_result_tready => subtractor_fifo_ready,
            m_axis_result_tdata => subtractor_out
        );

    -- FIFO for subtractor output
    subtractor_fifo_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => subtractor_fifo_valid,
            s_axis_tready  => subtractor_fifo_ready,
            s_axis_tdata   => subtractor_out,
            m_axis_tvalid  => broadcaster_tvalid,
            m_axis_tready  => broadcaster_tready,
            m_axis_tdata   => broadcaster_tdata
        );

    --broadcaster
    broadcaster_inst : axis_broadcaster_0
        port map (
            aclk => aclk,
            aresetn => aresetn,
            s_axis_tvalid => broadcaster_tvalid,
            s_axis_tready => broadcaster_tready,
            s_axis_tdata => broadcaster_tdata,
            m_axis_tvalid => broadcaster_out_tvalid,
            m_axis_tready => broadcaster_out_tready,
            m_axis_tdata => broadcaster_out_tdata
        );
        
        
    adder_g_plus_inst : entity work.Adder
        port map (
            aclk => aclk,
            s_axis_a_tvalid => broadcaster_out_tvalid(0),
            s_axis_a_tready => broadcaster_out_tready(0),
            s_axis_a_tdata => broadcaster_out_tdata(31 downto 0),
            s_axis_b_tvalid => thresh_g_plus_tvalid,
            s_axis_b_tready => thresh_g_plus_tready,
            s_axis_b_tdata => thresh_g_plus_tdata, 
            m_axis_result_tvalid => adder_out_tvalid,
            m_axis_result_tready =>adder_out_tready,
            m_axis_result_tdata => adder_out_tdata
        );
        
    subtractor_g_minus_inst: entity work.Subtractor
        port map (
            aclk => aclk,
            s_axis_a_tvalid => broadcaster_out_tvalid(0),
            s_axis_a_tready => broadcaster_out_tready(0),
            s_axis_a_tdata => broadcaster_out_tdata(31 downto 0),
            s_axis_b_tvalid => thresh_g_minus_tvalid,
            s_axis_b_tready => thresh_g_minus_tready,
            s_axis_b_tdata => thresh_g_minus_tdata, 
            m_axis_result_tvalid => sub1_out_tvalid,
            m_axis_result_tready =>sub1_out_tready,
            m_axis_result_tdata => sub1_out_tdata
        );
        
        subtractor1_fifo_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => sub1_out_tvalid,
            s_axis_tready  => sub1_out_tready,
            s_axis_tdata   => sub1_out_tdata,
            m_axis_tvalid  => fifo_sub1_out_tvalid,
            m_axis_tready  => fifo_sub1_out_tready,
            m_axis_tdata   => fifo_sub1_out_tdata
        );
        
        adder_fifo_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => adder_out_tvalid,
            s_axis_tready  => adder_out_tready,
            s_axis_tdata   => adder_out_tdata,
            m_axis_tvalid  => fifo_adder_out_tvalid,
            m_axis_tready  => fifo_adder_out_tready,
            m_axis_tdata   => fifo_adder_out_tdata
        );

    --drift
        drft_top: entity work.Subtractor
        port map (
            aclk => aclk,
            s_axis_a_tvalid => fifo_adder_out_tvalid,
            s_axis_a_tready => fifo_adder_out_tready,
            s_axis_a_tdata => fifo_adder_out_tdata,
            s_axis_b_tvalid => '1',
            s_axis_b_tready => open,
            s_axis_b_tdata => drift, 
            m_axis_result_tvalid => drift_out_tvalid,
            m_axis_result_tready =>drift_out_tready,
            m_axis_result_tdata => drift_out_tdata
        );
        
    --drift
        drft_bot: entity work.Subtractor
        port map (
            aclk => aclk,
            s_axis_a_tvalid => fifo_sub1_out_tvalid,
            s_axis_a_tready => fifo_sub1_out_tready,
            s_axis_a_tdata => fifo_sub1_out_tdata,
            s_axis_b_tvalid => '1',
            s_axis_b_tready => open,
            s_axis_b_tdata => drift, 
            m_axis_result_tvalid => drift_sub_tvalid,
            m_axis_result_tready =>drift_sub_tready,
            m_axis_result_tdata => drift_sub_tdata
        );
        
        -- Am uitat sa pun fifouri aici da la cate sunt eu nu mai stau sa schimb :))
        
       max_plus_inst : entity work.Max
        port map (
            aclk => aclk,
            s_axis_a_tvalid => '1',
            s_axis_a_tready => open,
            s_axis_a_tdata => x"00000000",
            s_axis_b_tvalid => drift_out_tvalid,
            s_axis_b_tready => drift_out_tready,
            s_axis_b_tdata => drift_out_tdata,
            m_axis_result_tvalid => max_out_tvalid,
            m_axis_result_tready => max_out_tready,
            m_axis_result_tdata => max_out_tdata
        );
        
        max_sub_inst : entity work.Max
        port map (
            aclk => aclk,
            s_axis_a_tvalid => '1',
            s_axis_a_tready => open,
            s_axis_a_tdata => x"00000000",
            s_axis_b_tvalid => drift_sub_tvalid,
            s_axis_b_tready => drift_sub_tready,
            s_axis_b_tdata => drift_sub_tdata,
            m_axis_result_tvalid => max_sub_tvalid,
            m_axis_result_tready => max_sub_tready,
            m_axis_result_tdata => max_sub_tdata
        );
        
        max_out_fifo_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => max_out_tvalid,
            s_axis_tready  => max_out_tready,
            s_axis_tdata   => max_out_tdata,
            m_axis_tvalid  => fifo_max_out_tvalid,
            m_axis_tready  => fifo_max_out_tready,
            m_axis_tdata   => fifo_max_out_tdata
        );
        
        max_sub_fifo_inst : fifo
        port map (
            s_axis_aresetn => aresetn,
            s_axis_aclk    => aclk,
            s_axis_tvalid  => max_sub_tvalid,
            s_axis_tready  => max_sub_tready,
            s_axis_tdata   => max_sub_tdata,
            m_axis_tvalid  => fifo_max_sub_tvalid,
            m_axis_tready  => fifo_max_sub_tready,
            m_axis_tdata   => fifo_max_sub_tdata
        );
        
        -- Threshold Comparator
    comparator_inst : entity work.ThresholdComparator
        port map (
            aclk => aclk,
            s_axis_g_plus_tvalid => fifo_max_out_tvalid,
            s_axis_g_plus_tready => fifo_max_out_tready,
            s_axis_g_plus_tdata => fifo_max_out_tdata, -- Maxed g+
            s_axis_g_minus_tvalid => fifo_max_sub_tvalid,
            s_axis_g_minus_tready => fifo_max_sub_tready,
            s_axis_g_minus_tdata => fifo_max_sub_tdata, -- Maxed g-
            s_axis_threshold_tvalid => '1',
            s_axis_threshold_tready => open,
            s_axis_threshold_tdata => threshold, -- Threshold constant
            m_axis_result_tvalid => m_axis_result_tvalid,
            m_axis_result_tready => m_axis_result_tready,
            m_axis_result_tdata => m_axis_result_tdata -- Output label
        );
        

end architecture;