<?php
class Config {
    public static $debug = true;

    public static $playerHealthStart = 100;
    public static $playerGoldStart = 100;

    public static function autoload($class) {
        $file = __DIR__ . "/include/" . str_replace('\\', '/', strtolower($class)) . ".inc";
        
        if (file_exists($file)) {
            require $file;
        } else {
            if (Config::$debug) {
                debug_print_backtrace();
            }
            
            die("Couldnt find file: $file\n");
        }
    }

    public static function randomWords($num = 3, $join = "") {
        $output = shell_exec("shuf -n$num /usr/share/dict/american-english");

        $words = preg_split("/\r\n|\n|\r/", $output);
        
        $ret = array();

        array_pop($words);
        
        foreach ($words as $word) {
            $bits = preg_split("/'/", $word);
            $word = strtolower($bits[0]);
            $ret[] = $word;
        }
        
        return implode($join, $ret);
    }
}

spl_autoload_register("Config::autoload");
