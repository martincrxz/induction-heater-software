/**
 * Created by Federico Manuel Gomez Peter
 * Date: 2/10/20
 */

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define APP_CONFIG_CONF_FILE_MISSING_MSG "El archivo de configuración no existe. Se creará uno"
#define APP_CONFIG_CONFIG_FILE_CREATE_ERROR_MSG "No se pudo crear/cargar el archivo %s"
#define APP_CONFIG_CONF_FILE_LOADED_MSG "Configuración cargada"
#define APP_CONFIG_GENERAL_CONF_MISSING_ERROR_MSG "No hay una configuración de la aplicación"
#define APP_CONFIG_CONFIG_FILE_UPDATED_MSG "Archivo de configuración actualizado"

#define THERMOCOUPLE_ERR_MSG_THERMOCOUPLE_TYPE_NOT_SUPPORTED "Error desconocido de la termocupla"
#define THERMOCOUPLE_ERR_MSG_CJ_TEMP_OUT_OF_RANGE "Temperatura de junta fría fuera de rango"
#define THERMOCOUPLE_ERR_MSG_TEMP_OUT_OF_RANGE "Temperatura fuera de rango"
#define THERMOCOUPLE_ERR_MSG_CJ_TMP_OVER_LIMIT "La temperatura de junta fría se excedió del limite superior"
#define THERMOCOUPLE_ERR_MSG_CJ_TMP_UNDER_LIMIT "La temperatura de junta fría se excedió del limite inferior"
#define THERMOCOUPLE_ERR_MSG_TMP_OVER_LIMIT "La temperatura se excedió del limite superior"
#define THERMOCOUPLE_ERR_MSG_TMP_UNDER_LIMIT "La temperatura se excedió del limite inferior"
#define THERMOCOUPLE_ERR_MSG_OVER_VOLTAGE "Hay sobretensión en la termocupla"
#define THERMOCOUPLE_ERR_MSG_OPEN_CIRCUIT "La termocupla está en circuito abierto"

#define SERIALPORT_INVALID_MSG_ERROR_MSG "Mensaje inválido"
#define SERIALPORT_SENDING_MSG "Enviando mensaje al microcontrolador: %s"
#define SERIALPORT_CONNECTED_MSG "El microcontrolador se conectó correctamente"
#define SERIALPORT_CONNECT_FAILED_MSG "No se puede abrir el puerto serie"
#define SERIAL_PORT_DEVICE_NOT_FOUND_MSG "Dispositivo no encontrado"
#define SERIAL_PORT_HANDLE_ERROR_MSG "Error en el puerto serie - %s (%i)"
#define SERIALPORT_RECEIVED_MSG "Mensaje recibido del microcontrolador: %s"
#define SERIALPORT_EMERGENCY_STOP_ACTIVATED_MSG "Se activó la parada de emergencia."
#define SERIALPORT_THERMOCOUPLE_ERROR_RECEIVED_MSG "Se recibió un mensaje de error de la termocupla: %s"
#define SERIALPORT_THERMOCOUPLE_CONFIG_ACK "Configuración de la termocupla cambiada exitosamente"
#define SERIALPORT_POWER_SET_ACK_MSG "Se cambió la potencia del horno exitosamente."
#define SERIALPORT_MANUAL_CONTROL_SET_ACK_MSG "Se configuró exitosamente el modo de control manual"
#define SERIALPORT_AUTOMATIC_CONTROL_SET_ACK_MSG "Se configuró exitosamente el modo de control automático"
#define SERIALPORT_UNKOWN_MSG "Mensaje desconocido"
#define SERIALPORT_CRC_FAILED_MSG "Falla en el CRC del mensaje del microcontrolador (Mensaje: %s, CRC esperado: %i, CRC recibido: %i)"

#define CLASSIC_PID_CONSTRUCTOR_MSG "Constructor de ClassicPID (kp= %.2f, kd= %.2f, ki= %.2f). Temperatura objetivo: %.0f °C"
#define CONTROL_ALGORITHM_EXIT_MSG "Ya existe un control automático activo"
#define CONTROL_ALGORITHM_TEMP_RECEIVED_MSG "Temperatura recibida: %0.2f °C"
#define CONTORL_ALGORITHM_OUTPUT_MSG "Vueltas a enviar: %i"
#define CONTROL_ALGORITHM_DESTROY_MSG "Destruyendo un objeto ControlAlgorithm"

#define FILE_CONTROL_PROCESS_FINISHED_MSG "El proceso finalizó exitosamente"
#define FILE_CONTROL_START_CLOSE_LOOP_MSG "Cambiando a lazo cerrado"
#define FILE_CONTROL_OPEN_LOOP_MSG "Lazo abierto, potencia actual: %0.2f %%"
#define FILE_CONTROL_START_OPEN_LOOP_MSG "Cambiando a lazo abierto"
#define FILE_CONTROL_CLOSED_LOOP_MSG "Lazo cerrado, cantidad de vueltas del potenciómetro: %i"

#define FUZZY_CONFIG_HEADER_MSG "Configuración de FuzzyLogic"
#define FUZZY_2X3_CONFIG_RULES_HEADERS_MSG "Reglas ([e,   de,   dkp,   dki,   dkd]):"
#define FUZZY_3X1_RULES_CONF_HEADER_MSG "Reglas ([e,   de,   ie,   dp]):"
#define FUZZY_ERROR_MEMBER_FUNCT_HEADER_MSG "Error en la configuración de las funciones de membresía"
#define FUZZY_DERIVATIVE_ERROR_HEADER_MSG "Configurción de las funciones de membresía para la derivada del error:"
#define FUZZY_INTEGRA_ERROR_MEMBER_FUNCT_HEADER_MSG "Configurción de las funciones de membresía para la integral del error:"
#define FUZZY_OUTPUT_POWER_HEADER_MSG "Configuración para las funciones de la potencia de salida"
#define FUZZY_2X3_KP_FUNCTION_MSG "Configuración para las funciones de salida de Kp"
#define FUZZY_2X3_KD_OUT_FUNCT_MSG "Configuración para las funciones de salida de Kd"
#define FUZZY_2X3_KI_OUT_FUNCT_MSG "Configuración para las funciones de salida de Ki"

#define JSON_CONFIG_FILE_COULDNT_BE_LOADED_MSG "No se pudo cargar el archivo json %s"
#define JSON_CONFIG_FILE_BAD_FORMAT_ELEMENT_SHOULD_BE_NUMBER_MSG "Mal formato del archivo, el elemento '%s' debe ser un número"
#define JSON_CONFIG_FILE_BAD_FORMAT_ELEMENT_SHOULD_BE_OBJECT_MSG "Mal formato del archivo, el elemento '%s' no es un objeto"
#define JSON_CONFIG_FILE_BAD_FORMAT_ELEMENT_SHOULD_BE_ARRAY_MSG "Mal formato del archivo, el elemento '%s' no es un arreglo"
#define JSON_CONFIG_FILE_BAD_FORMAT_ELEMENT_SHOULD_BE_STRING_MSG "Mal formato del archivo, el elemento '%s' no es un string"
#define JSON_CONFIG_FILE_BAD_FORMAT_ELEMENT_SHOULD_HAVE_4_NUMBERS_MSG "Mal formato del archivo, el elemento '%s' debe tener 4 números"
#define MEMBER_FUNCTIONS_BAD_FORMAT_MSG "Se debe cumplir que a (%f) <= b (%f) <= c (%f) <= d (%f)"

#define ZN_ERROR_LIMIT_TEMP_REACHED_MSG "Error en el proceso: se llegó a la temperatura de corte"

#define FILE_SAVED_MSG "Guardando archivo %s"
#define LOADING_FILE_MSG "Cargando archivo %s"
#define CONFIG_FILE_NOT_SELECTED "Archivo de configuración no seleccionado"

#define CLASSIC_CONTROL_VIEW_DATA_SAVED_MSG "Datos guardados."
#define CLASSIC_CONTROL_SAVE_DATA_FAILED_MSG "No se pudo guardar los datos. Revisar formato"
#define CLASSIC_CONTROL_ERROR_BAD_FORMAT_MSG "Parámetros inválidos del control clásico"

#define CONTORL_CONFIGURATION_DESTRUCTOR_MSG "Destruyendo el objeto ControlConfiguration"
#define CONTORL_CONFIGURATION_INIT_MSG "Inicializando el algorítmo de control"
#define CONTROL_CONFIGURATION_STOP_MSG "Parando el algoritmo de control"
#define CONTROL_CONFIGURATION_DATA_SAVED_MSG "Datos guardados en el archivo: %s"
#define CONTORL_CONFIGURATION_VARIABLE_UPDATED_MSG "Control %s actualizado (window_size: %i)"

#define FILE_DOESNT_EXIST_MSG "El archivo no existe"
#define FROM_FILE_CONTROL_VIEW_POWER_BAD_FORMAT_MSG "La potencia no puede superar 100%"
#define FILE_LOADED_CORRECTLY_MSG "El archivo se cargó correctamente"
#define CSV_BAD_FORMATTED_ERROR_MSG "El csv está mal formateado"
#define FROM_FILE_CONTROL_VIEW_BAD_FORMAT_MSG "Parámetros de control clásico inválido"

#define FUZZY_CONTROL_VIEW_TYPE_TOOLTIP_MSG "<b>Ayuda:</b><br>"\
                               "El modo de operación '2x3' toma el error de temperatura "\
                               "y la derivada del error para modificar los valores "\
                               "de las constantes kp, kd y ki del control PID clásico. "\
                               "Se debe brindar obligatoriamente valores iniciales de "\
                               "estas constantes.<br>"\
                               "El modo de operación '3x1' toma como entradas "\
                               "la temperatura, la derivada y la integral de estas, y "\
                               "se actua sobre la potencia de salida."
#define FUZZY_CONTROL_VIEW_PID_BAD_FORMAT "Las constantes de PID tienen un formato inválido"
#define FUZZY_CONTROL_VIEW_CONSTANTS_OK_MSG "Configuración correcta"
#define FUZZY_CONTROL_TEMPERATURE_NOT_SET_ERROR_MSG "La temperatura objetivo no puede estar vacía"
#define FUZZY_CONTROL_TARGET_TEMP_CHECK_FAILED_MSG "La temperatura objetivo tiene formato inválido"
#define FUZZY_CONTROL_VIEW_TARGET_CHECK_SUCCED_MSG "La temperatura objetivo se seteó correctamente"

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
#define GENERAL_VIEW_ENABLED_AUTOMATIC_CONTROL_MSG "Habilitando botones de control automático"
#define GENERAL_VIEW_DISABLED_AUTOMATIC_CONTROL_MSG "Deshabilitando botones de control automático"
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
