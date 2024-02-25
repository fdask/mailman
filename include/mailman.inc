<?php
class MailMan {
    // save the players term settings to restore at quit
    private $term;

    private $player;
    private $path;
    private $town;
    private $map;
    
    // hide/show the inventory screen
    private $inventory;
    
    // hide/show the travel select screen
    private $travelSelect;
    private $travelSelectIndex;

    public function __construct() {
        $this->player = new Player();
        $this->path = new Path();
        $this->town = new Town();
    
        $this->map = new Map();
        $this->map->addTown($this->town);
        
        $destTown = new Town();
        $this->map->addTown($destTown);
        $this->path->setDestTown($destTown->getName());
        $this->inventory = false;
        $this->travelSelect = false;
        $this->travelSelectIndex = 0;

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
        // our town
        $this->town = new Town();
        $this->map->addTown($this->town);

        // first destination town
        $d = new Town(2);
        $this->map->addTown($d);
    }

    public function gameLoop() {
        $this->term = `stty -g`;
		system("stty -icanon -echo");

        // initial draw
        echo $this;

        while (1) {
            if ($this->town) {
                $orig = $this->town->getName();
    
                $tArray = $this->map->getTowns($orig);
            }
    
            $pStatus = $this->player->getStatus();
            $c = $this->waitForInput();

            $tick = false;

            switch ($c) {
                case chr(10):
                    // enter key
                    if ($this->travelSelect) {
                        // do we have a path already?
                        $dest = $tArray[$this->travelSelectIndex];
                        if ($this->map->havePath($orig, $dest)) {
                            if (Config::$debug) {
                                echo "We have the path ($orig to $dest).  Loading...\n";
                            }
                            // we already have a path.  load it
                            $this->path = $this->map->getPath($orig, $dest);
                        } else if ($this->map->havePath($dest, $orig)) {
                            if (Config::$debug) {
                                echo "We have the reverse path ($dest to $orig).  Loading and reversing...\n";
                            }
                            // we have the reverse.  
                            $p = $this->map->getPath($dest, $orig);
                            $p->reversePath();
                            $this->map->addPath($p);
                            $this->path = $p;
                        } else {
                            // we do not have the path
                            if (Config::$debug) {
                                echo "We do not have the path.  Creating new one...\n";
                            }
                            $p = new Path($orig, $dest);
                        }

                        // player should be travelling
                        $this->player->setStatus(Player::$statusTravel);
                        $this->travelSelect = false;
                    }

                    break;
                case 'a':
                    // move left (to origin)
                    if ($pStatus == Player::$statusTravel) {
                        if ($this->path->yPos > 0) {
                            $this->path->yPos--;
                        }
                    }

                    break;
                case 'b':
                    if ($this->travelSelect) {
                        $this->travelSelect = false;
                    } else if ($this->inventory) {
                        $this->inventory = false;
                    } else if ($pStatus == Player::$statusStore) {
                        // go back to town
                        $this->player->setStatus(Player::$statusTown);
                    }

                    break;
                case 'd':
                    // move right (to destination)
                    if ($pStatus == Player::$statusTravel) {
                        if ($this->path->yPos <= $this->path->getDistance()) {
                            $this->path->yPos++;
                        }
                    }

                    break;
                case 'e':
                    if ($pStatus == Player::$statusTravel) {
                        // enter town
                        if ($this->path->yPos == 0) {
                            // return to Orig
                            $this->town = $this->map->getTown($this->path->origTown);
                            $this->player->setStatus(Player::$statusTown);
                        } else if ($this->path->yPos == $this->path->getDistance() + 1) {
                            // go to Dest
                            $this->town = $this->map->getTown($this->path->destTown);
                            $this->player->setStatus(Player::$statusTown);
                        }
                    }

                    break;
                case 'i':
                    // open inventory screen
                    if (!$this->inventory) {
                        $this->inventory = true;
                    }

                    break;
                case 'q':
					// quit the game
					$this->quit();

					exit;
                case 'r':
                    // rest in town
                    if ($pStatus == Player::$statusTown) {

                    }

                    break;
                case 't':
                    // travel
                    if ($pStatus == Player::$statusTown && !$this->travelSelect && count($this->map->getTowns($this->town->getName())) > 1) {
                        $this->travelSelect = true;
                    } else if ($pStatus == Player::$statusTown && $this->travelSelect) {
                        $this->travelSelect = false;
                        $this->player->setStatus(Player::$statusTravel);
                        $this->map->addTown($this->town);
                        $this->town = null;
                    }

                    break;
                case 'u':
                    // shop
                    if ($pStatus == Player::$statusTown) {
                        $this->player->setStatus(Player::$statusStore);
                    } 

                    break;
                case 'y':
                    // rumours
                    if ($pStatus == Player::$statusTown) {

                    }

                    break;
                default:
                    if (Config::$debug) {
                        die("Unhandled keypress '" . ord($c) . "'\n");
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

    private function quit() {
		// quit the game
		system("stty $this->term");

		exit;
	}

    public function __toString() {
        $ret = "\n";
        $ret .= $this->player;

        $pStatus = $this->player->getStatus();

        if ($pStatus == Player::$statusTravel) {
            $ret .= $this->path;
        }

        if ($pStatus == Player::$statusTown) {
            $ret .= $this->town;
        }

        $ret .= "\n";

        if ($this->travelSelect) {
            $townsArray = $this->map->getTowns($this->town->getName());
        }

        if ($this->inventory) {
            // show the inventory screen!
            $ret .= "INVENTORY\n\n";
            $ret .= "b) Back\n";
        } else if ($this->travelSelect) {
            // get towns array
            $ret .= "TRAVEL\n\n";

            if (count($this->map->getTowns($this->town->getName())) > 1) {
                $ret .= "< " . $townsArray[$this->travelSelectIndex] . " >\n\n";

                $ret .= "a) prev town\n";
                $ret .= "d) next town\n";
            } else {
                $ret .= "No Towns Available\n\n";
            }            

            $ret .= "b) back\n";
        } else {
            switch ($pStatus) {
                case Player::$statusTown:
                    $ret .= "r) rest\n";
                    $ret .= "t) travel\n";
                    $ret .= "y) hit up the rumour mill\n";
                    $ret .= "u) store\n";
                    $ret .= "i) inventory\n";
                    $ret .= "q) quit\n";
                    $ret .= "\n";

                    break;
                case Player::$statusTravel:
                    $ret .= "TRAVELLING\n\n";
                    
                    if ($this->path->yPos > 0) {
                        $ret .= "a) Back\n";
                    }

                    if ($this->path->yPos < $this->path->getDistance() + 1) {
                        $ret .= "d) Forward\n";
                    }
                    
                    if ($this->path->yPos == 0 || $this->path->yPos == $this->path->getDistance() + 1) {
                        $ret .= "e) enter town\n";
                    }

                    break;
                case Player::$statusStore:
                    $ret .= "Welcome to the store!\n\n";
                    $ret .= "b) back to town\n";

                    break;
                default:
                    if (Config::$debug) {
                        die("Unknown player status: $pStatus\n");
                    }
            }
        }

        return $ret;
    }
}