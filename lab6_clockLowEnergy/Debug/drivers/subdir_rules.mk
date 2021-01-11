################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/buttons.obj: C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers/buttons.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/CodeComposerWorkspace" --include_path="C:/CodeComposerWorkspace/lab6_clockLowEnergy" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=PART_TM4C123GH6PM --define=ccs="ccs" -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/rgb.obj: C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c123gxl/drivers/rgb.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --include_path="C:/CodeComposerWorkspace" --include_path="C:/CodeComposerWorkspace/lab6_clockLowEnergy" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --define=PART_TM4C123GH6PM --define=ccs="ccs" -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/$(basename $(<F)).d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


