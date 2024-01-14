#include <stdio.h>

#include <esp_task_wdt.h>

#include "display.h"
#include "gnarl.h"
#include "rfm95.h"

void app_main(void) {
	   esp_task_wdt_config_t wdtc;
   wdtc.idle_core_mask = 0;
   wdtc.idle_core_mask |= (1 << 0);
   wdtc.idle_core_mask |= (1 << 1);
   wdtc.timeout_ms = WDT_TIMEOUT_SECONDS;
   wdtc.trigger_panic = true;
   esp_task_wdt_init(&wdtc);
	ESP_LOGI(TAG, "%s", SUBG_RFSPY_VERSION);
	rfm95_init();
	uint8_t v = read_version();
	ESP_LOGD(TAG, "radio version %d.%d", version_major(v), version_minor(v));
	set_frequency(PUMP_FREQUENCY);
	ESP_LOGD(TAG, "frequency set to %lu Hz", read_frequency());
	display_init();
	gnarl_init();
}
