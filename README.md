# reaper: command to monitor and annotate a process tree

```reaper <annotations> -- <command>```

__reaper__ acts as a process tree subreaper for its given command, and will wait for it to completely finish execution.

It can be used as convenient checkpoint between complex process trees, and will contain and monitor any potential runaway processes.

```
konsole(193319)---bash(193366)---reaper(1522050)-+-fc2-electron(1522075)-+-fc2-electron(1522077)---fc2-electron(1522107)
                                                 |                       |-fc2-electron(1522078)
                                                 |                       |-fc2-electron(1522111)
                                                 |                       `-fc2-electron(1522139)
                                                 `-fcade(1522353)---fcade(1522356)
```

Anything before `--` is ignored on the command-line, which can be used to annotate a given process tree with metadata for external parties to inspect. Thus, any process in the sub-command can reliably be associated with such metadata:

```reaper GameId=570 -- ./run_dota_launcher.sh```
