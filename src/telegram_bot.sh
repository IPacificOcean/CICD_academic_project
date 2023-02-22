#!/bin/bash

TELEGRAM_BOT_TOKEN="6030680083:AAG100mi_DmyLPmOdv2hjUuQq-KaHobYge4"
TELEGRAM_USER_ID=198632649
TIME=60
STATUS="$(echo $1 "$CI_JOB_STATUS")"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
