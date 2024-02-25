<?php
class Player {
    private $gold;
    private $health;
   
    private $status;

    public static $statusTown = "TOWN";
    public static $statusTravel = "TRAVEL";
    public static $statusStore = "STORE";
    
    public function __construct() {
        $this->reset();
    }

    public function reset() {
        $this->gold = Config::$playerGoldStart;
        $this->health = Config::$playerHealthStart;
        $this->status = Player::$statusTown;
    }

    public function getGold() {
        return $this->gold;
    }

    public function getHealth() {
        return $this->health;
    }

    public function getStatus() {
        return $this->status;
    }

    public function setStatus($s) {
        if (!in_array($s, array(Player::$statusTown, Player::$statusStore, Player::$statusTravel))) {
            return false;
        }

        $this->status = $s;

        return true;
    }

    public function __toString() {
        $ret = "GOLD: " . $this->getGold() . " ";
        $ret .= "HEALTH: " . $this->getHealth() . " ";
        $ret .= "STATUS: " . $this->getStatus();
        $ret .= "\n";

        return $ret;
    }
}