/**
 * Created by Federico Manuel Gomez Peter
 * Date: 2/10/20
 */

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define APP_CONFIG_FILEPATH "app_configuration.json"
#define APP_CONFIG_CONF_FILE_MISSING_MSG "Configuration file doesn't exist, creating it"
#define APP_CONFIG_CONFIG_FILE_CREATE_ERROR_MSG "Couldn't create/load json file %s"
#define APP_CONFIG_CONF_FILE_LOADED_MSG "Configuration loaded"
#define APP_CONFIG_GENERAL_CONF_MISSING_ERROR_MSG "There is no general configuration"
#define APP_CONFIG_BAD_FORMAT_MSG "Bad config format, general/log_level is not an array"
#define APP_CONFIG_BAD_FORMAT_WINDOW_SIZE_MUST_BE_NUMBER_MSG "Bad config format, general/window_size must be a number"
#define APP_CONFIG_CONFIG_FILE_UPDATED_MSG "Json config file updated"

#define PROTOCOL_INVALID_MSG_ERROR_MSG "Invalid message"

#define THERMOCOUPLE_ERR_MSG_THERMOCOUPLE_TYPE_NOT_SUPPORTED "Non-supported thermocouple error"
#define THERMOCOUPLE_ERR_MSG_CJ_TEMP_OUT_OF_RANGE "Cold junction temperature out of range."
#define THERMOCOUPLE_ERR_MSG_TEMP_OUT_OF_RANGE "Temperature out of range."
#define THERMOCOUPLE_ERR_MSG_CJ_TMP_OVER_LIMIT "Cold junction temperature over high limit."
#define THERMOCOUPLE_ERR_MSG_CJ_TMP_UNDER_LIMIT "Cold junction temperature under low limit."
#define THERMOCOUPLE_ERR_MSG_TMP_OVER_LIMIT "Temperature over high limit."
#define THERMOCOUPLE_ERR_MSG_TMP_UNDER_LIMIT "Temperature under low limit."
#define THERMOCOUPLE_ERR_MSG_OVER_VOLTAGE "Over voltage"
#define THERMOCOUPLE_ERR_MSG_OPEN_CIRCUIT "Open thermocouple."

#define SERIALPORT_SENDING_MSG "Sending message: %s"
#define SERIALPORT_CONNECTED_MSG "Serial port connected."
#define SERIALPORT_CONNECT_FAILED_MSG "Cannot open serial port."
#define SERIAL_PORT_DEVICE_NOT_FOUND_MSG "Device not found."
#define SERIAL_PORT_HANDLE_ERROR_MSG "Serial port error - %s (%i)"
#define SERIALPORT_RECEIVED_MSG "Message received: %s"
#define SERIALPORT_EMERGENCY_STOP_ACTIVATED_MSG "Se activo la parada de emergencia."
#define SERIALPORT_THERMOCOUPLE_ERROR_RECEIVED_MSG "Thermocouple fault message: %s"
#define SERIALPORT_THERMOCOUPLE_CONFIG_ACK "Thermocouple configuration acknowledge message "
#define SERIALPORT_POWER_SET_ACK_MSG "Power set acknowledge message."
#define SERIALPORT_MANUAL_CONTROL_SET_ACK_MSG "Manual control activated message."
#define SERIALPORT_AUTOMATIC_CONTROL_SET_ACK_MSG "Automatic control activated message."
#define SERIALPORT_UNKOWN_MSG "Unknown message"
#define SERIALPORT_CRC_FAILED_MSG "CRC failed (Message: %s, Expected: %c, Received: %i)"

#define CLASSIC_PID_CONSTRUCTOR_MSG "ClassicPID constructor ( kp= %.2f, kd= %.2f, ki= %.2f). Target temperature: %.0f °C"
#define CONTROL_ALGORITHM_EXIT_MSG "Exiting control algorithm"
#define CONTROL_ALGORITHM_TEMP_RECEIVED_MSG "Recibido %0.2f °C"
#define CONTORL_ALGORITHM_OUTPUT_MSG "Vueltas a enviar: %i"
#define CONTROL_ALGORITHM_DESTROY_MSG "Destroying ControlAlgorithm"

#define FILE_CONTROL_PROCESS_FINISHED_MSG "Process finished"
#define FILE_CONTROL_START_CLOSE_LOOP_MSG "Changing to closed loop"
#define FILE_CONTROL_OPEN_LOOP_MSG "Open loop. Current power: %0.2f %%"
#define FILE_CONTROL_START_OPEN_LOOP_MSG "Changing to open loop"
#define FILE_CONTROL_CLOSED_LOOP_MSG "Closed loop. taps: %i"

#define FUZZY_CONFIG_HEADER_MSG "FuzzyLogic configuration"
#define FUZZY_2X3_CONFIG_RULES_HEADERS_MSG "Rules ([e,   de,   dkp,   dki,   dkd]):"
#define FUZZY_3X1_RULES_CONF_HEADER_MSG "Rules: [e,   de,   ie,   dp]"
#define FUZZY_ERROR_MEMBER_FUNCT_HEADER_MSG "Error member functions configuration"
#define FUZZY_DERIVATIVE_ERROR_HEADER_MSG "Derivative error member functions configuration"
#define FUZZY_INTEGRA_ERROR_MEMBER_FUNCT_HEADER_MSG "Integral error member functions configuration"
#define FUZZY_OUTPUT_POWER_HEADER_MSG "Power output functions configuration"
#define FUZZY_2X3_KP_FUNCTION_MSG "Kp output functions configuration"
#define FUZZY_2X3_KD_OUT_FUNCT_MSG "Kd output functions configuration"
#define FUZZY_2X3_KI_OUT_FUNCT_MSG "Ki output functions configuration"

#define FUZZY_LOGIC_ERROR_LOAD_FAILED_MSG "Couldn't load json file %s"
#define FUZZY_LOGIC_FILE_BAD_FORMAT_ELEMNT_IS_NOT_OBJECT_MSG "Element '%s' is not an object"
#define FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_ARRAY_MSG "Element '%s' is not an array"
#define FUZZY_LOGIC_BAD_FORMAT_ELEMENT_IS_NOT_STRING "Element '%s' is not a string"
#define FUZZY_LOGIC_FILE_BAD_FORMAT_ELEMENT_SHOULD_HAVE_4_VALUES "Element '%s' should have 4 numbers"
#define MEMBER_FUNCTIONS_BAD_FORMAT_MSG "Se debe cumplir que a (%f) <= b (%f) <= c (%f) <= d (%f)"

#define ZN_ERROR_LIMIT_TEMP_REACHED_MSG "Error en el proceso: se llegó a la temperatura de corte"

#define FILE_SAVED_MSG "Guardando archivo %s"
#define LOADING_FILE_MSG "loading file %s"
#define CONFIG_FILE_NOT_SELECTED "Config file not selected"

#define CLASSIC_CONTROL_VIEW_DATA_SAVED_MSG "Datos guardados."
#define CLASSIC_CONTROL_SAVE_DATA_FAILED_MSG "No se pudo guardar los datos. Revisar formato"
#define CLASSIC_CONTROL_ERROR_BAD_FORMAT_MSG "Invalid format of classic control parameters file"

#define CONTORL_CONFIGURATION_DESTRUCTOR_MSG "Destroying ControlConfiguration"
#define CONTORL_CONFIGURATION_INIT_MSG "Initiating control algorithm"
#define CONTROL_CONFIGURATION_STOP_MSG "Stopping control algorithm"
#define CONTROL_CONFIGURATION_DATA_SAVED_MSG "Data saved in file: %s"
#define CONTORL_CONFIGURATION_VARIABLE_UPDATED_MSG "Control %s updated (window_size: %i)"

#define FILE_DOESNT_EXIST_MSG "El archivo no existe"
#define FROM_FILE_CONTROL_VIEW_POWER_BAD_FORMAT_MSG "La potencia no puede superar 100%"
#define FILE_LOADED_CORRECTLY_MSG "El archivo se cargó correctamente"
#define CSV_BAD_FORMATTED_ERROR_MSG "El csv está mal formateado"
#define FROM_FILE_CONTROL_VIEW_BAD_FORMAT_MSG "Invalid format of classic control parameters file"

#define FUZZY_CONTROL_VIEW_TYPE_TOOLTIP_MSG "<b>Ayuda:</b><br>"\
                               "El modo de operación '2x3' toma el error de temperatura "\
                               "y la derivada del error para modificar los valores "\
                               "de las constantes kp, kd y ki del control PID clásico. "\
                               "Se debe brindar obligatoriamente valores iniciales de "\
                               "estas constantes.<br>"\
                               "El modo de operación '3x1' toma como entradas "\
                               "la temperatura, la derivada y la integral de estas, y "\
                               "se actua sobre la potencia de salida."
#define FUZZY_CONTROL_VIEW_PID_BAD_FORMAT "PID constants failed"
#define FUZZY_CONTROL_VIEW_CONSTANTS_OK_MSG "PID constants check passed"
#define FUZZY_CONTROL_TEMPERATURE_NOT_SET_ERROR_MSG "Target temperature empty."
#define FUZZY_CONTROL_TARGET_TEMP_CHECK_FAILED_MSG "Target temperature check failed."
#define FUZZY_CONTROL_VIEW_TARGET_CHECK_SUCCED_MSG "Target temperature check succeed."

#define ZN_ACTIVATED_MSG "Se activo el proceso de Ziegler-Nichols"
#define ZN_CANT_BE_ACTIVATED_MSG "Se quiere activar el ZN pero hay un control activo"
#define ZN_SUCCESFULY_FINISHED "Se calcularon los parámetros exitosamente"
#define ZN_INTERRUPTED "Se interrumpe el proceso"
#define AUTOTUNNING_VIEW_BAD_ARGUMENTS "Error en los parámetros."
#define AUTOTUNING_VIEW_PROCESSING_MSG "Calculando..."
#define AUTOTUNNING_NO_PROCEES_TO_DEACTIVATE_MSG "No hay proceso para desactivar"

#define AUTOMATIC_CONTROL_VIEW_BAD_ARGUMENTS_ERROR_MSG "Hay un error en los parámetros de control."
#define AUTOMATIC_CONTROL_VIEW_PROCESS_ACTIVATED_MSG "Se activó el proceso de control correctamente"
#define AUTOMATIC_CONTROL_VIEW_PROCESS_ACTIVE_ERROR_MSG "Hay un proceso activo."
#define AUTOMATIC_CONTROL_PROCESS_DEACTIVATED_MSG "Proceso detenido correctamente"
#define AUTOMATIC_CONTROL_VIEW_NO_PROCESS_ACTIVE_MSG "No hay proceso que desactivar"

#define GENERAL_VIEW_TEMPERATURE_RECEIVED_MSG "Temperatura recibida: %.2f °C"
#define GENERAL_VIEW_COLD_JUNCTION_TEMP_MSG "Temperatura de juntura fría: %.2f °C"
#define GENERAL_VIEW_FRECUENCY_MSG "Frecuencia recibida: %.2f Hz"
#define GENERAL_VIEW_CURRENT_MSG "Corriente recibida: %.2f A"
#define GENERAL_VIEW_ENABLED_AUTOMATIC_CONTROL_MSG "Enabling automatic buttons"
#define GENERAL_VIEW_DISABLED_AUTOMATIC_CONTROL_MSG "Disabling automatic buttons"
#define GENERAL_VIEW_CONECTION_LOST_MSG "Se perdió la conexión con el microcontrolador"
#define GENERAL_VIEW_USB_DISCONNECTED_MSG "USB desconectado"
#define GENERAL_VIEW_THERMOCOUPLE_FAULT_MSG "Falla en termocupla"

#define OK_MSG "OK"
#define MANUAL_MODE_MSG "MANUAL"
#define AUTOMATIC_MODE_MSG "AUTOMATICO"
#define ON_MSG "ON"
#define OFF_MSG "OFF"

#define INVALID_POWER_MSG "Potencia inválida"
#define MSG_SENT_MSG "Mensaje enviado"

#define UNKNOWN_ERROR_MSG "Unknown error on %s thread."

#endif //__MESSAGES_H__
