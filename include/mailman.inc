<?php
class MailMan {
    private $term;

    public function __construct() {
        $this->reset();
        $this->gameLoop();
    }

    public function waitForInput() {
		$input = '';

		$read = [STDIN];
		$write = null;
		$except = null;

		readline_callback_handler_install('', function() {});

		// Read characters from the command line one at a time until there aren't any more to read
		do {
			$input .= fgetc(STDIN);
		} while (stream_select($read, $write, $except, 0, 1));

		readline_callback_handler_remove();

		return $input;
	}

    private function reset() {

    }

    public function gameLoop() {
        $this->term = `stty -g`;
		system("stty -icanon -echo");

        while (1) {
            $c = $this->waitForInput();

            $tick = false;

            switch ($c) {
                case 'q':
					// quit the game
					system("stty $this->term");

					exit;
                default:
                    if (Config::$debug) {
                        die("Unhandled keypress '$c'\n");
                    }
            }

            if ($tick) {
                $this->tick();
            }

            // draw
            echo $this;
        }
    }

    private function tick() {

    }

    private function gameOver() {
		echo "GAME OVER\n\n";

		// quit the game
		system("stty $this->term");

		exit;
	}

    public function __toString() {

    }
}