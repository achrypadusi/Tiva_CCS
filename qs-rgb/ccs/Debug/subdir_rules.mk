################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
qs-rgb.obj: C:/CodeComposerWorkspace/qs-rgb/qs-rgb.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/qs-rgb" --include_path="C:/CodeComposerWorkspace/qs-rgb/ccs" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

rgb_commands.obj: C:/CodeComposerWorkspace/qs-rgb/rgb_commands.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/qs-rgb" --include_path="C:/CodeComposerWorkspace/qs-rgb/ccs" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_ccs.obj: C:/CodeComposerWorkspace/qs-rgb/startup_ccs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/qs-rgb" --include_path="C:/CodeComposerWorkspace/qs-rgb/ccs" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/qs-rgb" --include_path="C:/CodeComposerWorkspace/qs-rgb/ccs" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


