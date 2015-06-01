ipcs -s | grep ic14b070 | cut -f2 -d" " | xargs -I {} echo 'ipcrm -s {}'
ipcs -m | grep ic14b070 | cut -f2 -d" " | xargs -I {} echo 'ipcrm -m {}'
ipcs -q | grep ic14b070 | cut -f2 -d" " | xargs -I {} echo 'ipcrm -q {}'
