library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity cache_controller is
    port (
        CLK       : in std_logic;
        ADDR      : in std_logic_vector(31 downto 0);
        DATA_IN   : in std_logic_vector(63 downto 0);
        DATA_OUT  : out std_logic_vector(63 downto 0);
        RD        : in std_logic;
        WR        : in std_logic;
        HIT       : out std_logic;
        BUSY      : out std_logic;
        -- Main memory interface
        MM_ADDR   : out std_logic_vector(31 downto 0);
        MM_DATA_IN : in std_logic_vector(63 downto 0);
        MM_DATA_OUT : out std_logic_vector(63 downto 0);
        MM_RD     : out std_logic;
        MM_WR     : out std_logic;
        MM_BUSY   : in std_logic
    );
end cache_controller;

architecture behavioral of cache_controller is
    component tag_memory
        port (
            CLK    : in std_logic;
            A      : in std_logic_vector(12 downto 0);
            WR     : in std_logic;
            DIN    : in std_logic_vector(13 downto 0);
            DOUT   : out std_logic_vector(13 downto 0);
            MATCH  : out std_logic
        );
    end component;

    component data_memory
        port (
            CLK    : in std_logic;
            A      : in std_logic_vector(14 downto 0);
            WR     : in std_logic;
            DIN    : in std_logic_vector(63 downto 0);
            DOUT   : out std_logic_vector(63 downto 0)
        );
    end component;

    -- Address breakdown (32 bits):
    -- [31:18] Tag (14 bits)
    -- [17:5]  Index (13 bits)
    -- [4:0]   Displacement (5 bits)

    signal tag_index   : std_logic_vector(12 downto 0);
    signal tag_data    : std_logic_vector(13 downto 0);
    signal tag_match   : std_logic;
    signal tag_write   : std_logic;
    signal data_addr   : std_logic_vector(14 downto 0);
    signal data_write  : std_logic;
    
    type state_type is (IDLE, CHECK_TAG, WRITE_BACK, FETCH, UPDATE);
    signal state : state_type := IDLE;
begin
    tag_index <= ADDR(17 downto 5);
    tag_data <= ADDR(31 downto 18);
    data_addr <= ADDR(18 downto 4);  -- Index + block offset

    -- Tag memory instance
    tag_mem: tag_memory 
    port map (
        CLK    => CLK,
        A      => tag_index,
        WR     => tag_write,
        DIN    => tag_data,
        DOUT   => open,
        MATCH  => tag_match
    );

    -- Data memory instance
    data_mem: data_memory
    port map (
        CLK    => CLK,
        A      => data_addr,
        WR     => data_write,
        DIN    => DATA_IN,
        DOUT   => DATA_OUT
    );

    -- Cache controller state machine
    process(CLK)
    begin
        if rising_edge(CLK) then
            case state is
                when IDLE =>
                    if RD = '1' or WR = '1' then
                        state <= CHECK_TAG;
                        BUSY <= '1';
                    else
                        BUSY <= '0';
                    end if;

                when CHECK_TAG =>
                    if tag_match = '1' then  -- Cache hit
                        HIT <= '1';
                        if WR = '1' then
                            data_write <= '1';
                        end if;
                        state <= IDLE;
                    else  -- Cache miss
                        HIT <= '0';
                        state <= FETCH;
                        MM_ADDR <= ADDR;
                        MM_RD <= '1';
                    end if;

                when FETCH =>
                    if MM_BUSY = '0' then
                        -- Update cache with fetched data
                        tag_write <= '1';
                        data_write <= '1';
                        state <= UPDATE;
                    end if;

                when UPDATE =>
                    tag_write <= '0';
                    data_write <= '0';
                    if WR = '1' then
                        data_write <= '1';
                    end if;
                    state <= IDLE;

                when others =>
                    state <= IDLE;
            end case;
        end if;
    end process;
end behavioral;