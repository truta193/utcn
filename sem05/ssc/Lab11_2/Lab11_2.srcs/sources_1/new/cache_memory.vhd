library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity cache_memory is
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
address : in STD_LOGIC_VECTOR(15 downto 0);
data_in : in STD_LOGIC_VECTOR(31 downto 0);
write_enable : in STD_LOGIC;
data_out : out STD_LOGIC_VECTOR(31 downto 0);
hit : out STD_LOGIC
);
end cache_memory;
architecture Behavioral of cache_memory is
component tag_memory
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
index : in STD_LOGIC_VECTOR(5 downto 0);
tag_in : in STD_LOGIC_VECTOR(7 downto 0);
valid_in : in STD_LOGIC;
write_enable : in STD_LOGIC;
tag_out : out STD_LOGIC_VECTOR(7 downto 0);
valid_out : out STD_LOGIC
);
end component;
component data_memory
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
index : in STD_LOGIC_VECTOR(5 downto 0);
data_in : in STD_LOGIC_VECTOR(31 downto 0);
write_enable : in STD_LOGIC;
data_out : out STD_LOGIC_VECTOR(31 downto 0)
);
end component;
component line_decoder
Port (
index : in STD_LOGIC_VECTOR(5 downto 0);
select_line : out STD_LOGIC_VECTOR(63 downto 0)
);
end component;
component cache_control
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
hit : in STD_LOGIC;
miss : in STD_LOGIC;
update : out STD_LOGIC
);
end component;
signal index : STD_LOGIC_VECTOR(5 downto 0);
signal tag : STD_LOGIC_VECTOR(7 downto 0);
signal offset : STD_LOGIC_VECTOR(1 downto 0);
signal tag_out : STD_LOGIC_VECTOR(7 downto 0);
signal valid_out : STD_LOGIC;
signal data_out_internal : STD_LOGIC_VECTOR(31 downto 0);
signal select_line : STD_LOGIC_VECTOR(63 downto 0);
signal update : STD_LOGIC;
signal hit_internal : STD_LOGIC;
signal miss_internal : STD_LOGIC;
begin
tag <= address(15 downto 8);
index <= address(7 downto 2);
offset <= address(1 downto 0);
miss_internal <= not hit_internal;
tag_memory_inst: tag_memory
Port map (
clk => clk,
reset => reset,
index => index,
tag_in => tag,
valid_in => '1',
write_enable => update,
tag_out => tag_out,
valid_out => valid_out
);
data_memory_inst: data_memory
Port map (
clk => clk,
reset => reset,
index => index,
data_in => data_in,
write_enable => write_enable,
data_out => data_out_internal
);
line_decoder_inst: line_decoder
Port map (
index => index,
select_line => select_line
);
fsm_inst: cache_control
Port map (
clk => clk,
reset => reset,
hit => hit_internal,
miss => miss_internal,
update => update
);
process(tag, tag_out, valid_out)
begin
if (tag = tag_out and valid_out = '1') then
hit_internal <= '1';
else
hit_internal <= '0';
end if;
end process;
data_out <= data_out_internal;
hit <= hit_internal;
end Behavioral;