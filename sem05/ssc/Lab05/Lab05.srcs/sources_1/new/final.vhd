library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity final is
  Port (
    data_in : in std_logic_vector(7 downto 0);
    btn_rd : in std_logic;
    btn_wr : in std_logic;
    clk: in std_logic;
    rst: in std_logic;
    cat: out std_logic_vector(6 downto 0);
    an : out std_logic_vector(3 downto 0);
    empty : out std_logic;
    full: out std_logic
   );
end final;

architecture Behavioral of final is
component debouncer is
  Port ( clk : in std_logic;
        btn : in std_logic;
        en : out std_logic );
end component;

component display_7seg is
    Port ( digit0 : in STD_LOGIC_VECTOR (3 downto 0);
           digit1 : in STD_LOGIC_VECTOR (3 downto 0);
           digit2 : in STD_LOGIC_VECTOR (3 downto 0);
           digit3 : in STD_LOGIC_VECTOR (3 downto 0);
           clk : in STD_LOGIC;
           cat : out STD_LOGIC_VECTOR (6 downto 0);
           an : out STD_LOGIC_VECTOR (3 downto 0));
end component;

component fifo8x8 is
    Port (
        clk        : in std_logic;
        rst        : in std_logic;
        wrinc      : in std_logic;
        rdinc      : in std_logic;
        rd         : in std_logic;
        wr         : in std_logic;
        data_in    : in std_logic_vector(7 downto 0);
        data_out   : out std_logic_vector(7 downto 0)
    );
end component;

component fifo_ctrl is
    Port (
        rd      : in  std_logic;
        wr      : in  std_logic;
        clk     : in  std_logic;
        rst     : in  std_logic;
        rdinc   : out std_logic;
        wrinc   : out std_logic;
        empty   : out std_logic;
        full    : out std_logic
    );
end component;

signal rd, wr, rdinc, wrinc : std_logic := '0';
signal data_out : std_logic_vector(7 downto 0) := "00000000";

begin

    dbc1: debouncer port map  (clk, btn_rd, rd);
    dbc2: debouncer port map  (clk, btn_wr, wr);

    fctrl: fifo_ctrl port map (rd, wr, clk, rst, rdinc, wrinc, empty, full);

    fifo: fifo8x8 port map (clk, rst, wrinc, rdinc, rd, wr, data_in, data_out);

    ssd: display_7seg port map (
        digit0 => data_out(3 downto 0),      -- Lower 4 bits of data_out
        digit1 => data_out(7 downto 4),      -- Upper 4 bits of data_out
        digit2 => data_in(3 downto 0),       -- Lower 4 bits of data_in
        digit3 => data_in(7 downto 4),       -- Upper 4 bits of data_in
        clk    => clk,                       -- Clock input
        cat    => cat,                       -- 7-segment display output
        an     => an                         -- Anode control output
    );
end Behavioral;
