library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity cache_control is
Port (
clk : in STD_LOGIC;
reset : in STD_LOGIC;
hit : in STD_LOGIC;
miss : in STD_LOGIC;
update : out STD_LOGIC
);
end cache_control;
architecture Behavioral of cache_control is
type state_type is (SEARCH, UPDATE_STATE, RD_WR);
signal current_state, next_state : state_type;
begin
process(clk, reset)
begin
if reset = '1' then
current_state <= SEARCH;
elsif rising_edge(clk) then
current_state <= next_state;
end if;
end process;
process(current_state, hit, miss)
begin
case current_state is
when SEARCH =>
if hit = '1' then
next_state <= RD_WR;
elsif miss = '1' then
next_state <= UPDATE_STATE;
else
next_state <= SEARCH;
end if;
when UPDATE_STATE =>
next_state <= SEARCH;
when RD_WR =>
next_state <= SEARCH;
end case;
end process;
update <= '1' when current_state = UPDATE_STATE else '0';
end Behavioral;