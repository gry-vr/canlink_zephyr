board_runner_args(stm32cubeprogrammer "--port=swd" "--reset-mode=hw")
include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)

board_runner_args(openocd
  "--cmd-pre-init=source [find interface/stlink.cfg]"
  "--cmd-pre-init=transport select hla_swd"
  "--cmd-pre-init=source [find target/stm32f7x.cfg]"
)
include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)