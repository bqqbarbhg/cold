#include "game.h"
#include <cold/platform/application.h>
#include <cold/render/render.h>
#include <cold/platform/os.h>

namespace cold { namespace game {

void Game::run() {
	initialize();
	application.update_elapsed();
	while (application.is_running()) {
		application.poll_events();
		float elapsed = application.update_elapsed();
		time += elapsed;
		update(elapsed);
		draw();
		render::update();

#ifdef _DEBUG
		render::error_t err;
		if (render::get_error(err))
			os::message_box("Render Error", render::get_error_string(err).c_str(), os::MBOX_ERROR);
#endif
	}
	uninitialize();
}

} }