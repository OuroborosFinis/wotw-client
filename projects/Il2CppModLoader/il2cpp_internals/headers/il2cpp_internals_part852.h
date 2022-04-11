namespace app {
struct InstantStopBehaviour {
  struct InstantStopBehaviour__Class *klass;
  struct MonitorData *monitor;
  struct InstantStopBehaviour__Fields fields;
};
struct InstantStopBehaviour__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData get_Info;
  VirtualInvokeData PerformSanityCheck;
  VirtualInvokeData get_Status;
  VirtualInvokeData Execute;
  VirtualInvokeData Reset;
  VirtualInvokeData InitializeBehaviourNode;
  VirtualInvokeData CompareTo;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData OnDestroy;
  VirtualInvokeData MoonCleanup;
  VirtualInvokeData Execute_1;
  VirtualInvokeData Reset_1;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData OnReset;
  VirtualInvokeData OnBehaviourTreeInitialize;
  VirtualInvokeData OnExecute;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData CacheSerializedComponents;
  VirtualInvokeData OnEntityInitialized;
};
struct InstantStopBehaviour__StaticFields {
};
struct InstantStopBehaviour__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct InstantStopBehaviour__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct InstantStopBehaviour__VTable vtable;
};

struct MinerBuilderTurningBehaviour__Fields {
  struct TurningBehaviour__Fields _;
  struct LegacyTimelineSequence * turningSequence;
  float m_lookDirection;
};
struct MinerBuilderTurningBehaviour {
  struct MinerBuilderTurningBehaviour__Class *klass;
  struct MonitorData *monitor;
  struct MinerBuilderTurningBehaviour__Fields fields;
};
struct MinerBuilderTurningBehaviour__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData get_Entity;
  VirtualInvokeData OnExecuteTask_1;
  VirtualInvokeData OnInitializeTask_1;
  VirtualInvokeData OnEnterTask_1;
  VirtualInvokeData OnExitTask_1;
  VirtualInvokeData OnResetTask_1;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData UpdateState;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData GetStateId;
  VirtualInvokeData get_TargetLookDirectionX;
  VirtualInvokeData set_TargetLookDirectionX;
  VirtualInvokeData PlayAnimation;
  VirtualInvokeData ShouldEndBehaviour;
  VirtualInvokeData get_IsPlaying;
  VirtualInvokeData CanCancel;
};
struct MinerBuilderTurningBehaviour__StaticFields {
};
struct MinerBuilderTurningBehaviour__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct MinerBuilderTurningBehaviour__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct MinerBuilderTurningBehaviour__VTable vtable;
};

enum SandWormDashBehaviourNew_State__Enum : int32_t {
  SandWormDashBehaviourNew_State__Enum_Unset = 0,
  SandWormDashBehaviourNew_State__Enum_Antic = 1,
  SandWormDashBehaviourNew_State__Enum_Dash = 2,
  SandWormDashBehaviourNew_State__Enum_Resolve = 3,
};
struct SandWormDashBehaviourNew_State__Enum__Boxed {
  struct Enum__Class *klass;
  struct MonitorData *monitor;
  enum SandWormDashBehaviourNew_State__Enum value;
};
struct SandWormDashBehaviourNew__Fields {
  struct EntityBehaviourNode_1_SandWormEntity___Fields _;
  enum NavigationType__Enum DashZone;
  struct MoonReference_1_UnityEngine_GameObject_ * DashTarget;
  struct MoonFloat * PredictionTime;
  struct MoonFloat * FollowTargetTime;
  struct SandWormSandDigLocomotionBehaviour_SpeedEntry AnticSpeed;
  struct SandWormSandDigLocomotionBehaviour_SpeedEntry DashSpeed;
  struct SandWormSandDigLocomotionBehaviour_SpeedEntry ResolveSpeed;
  float AnticipationCompressDuration;
  float FollowThroughDuration;
  float SlowdownTime;
  float TrailWidth;
  struct MoonTimeline * Timeline;
  struct MoonTimeline * HitWallTimeline;
  struct Event_1 * DashPrepareSound;
  struct Event_1 * DashAttackSound;
  float m_anticipationTime;
  float m_dashTime;
  struct Rigidbody * m_targetRigidbody;
  struct SandWormLocomotion * m_wormLocomotion;
  float m_originalTrailWidth;
  float m_followTargetTimer;
  struct Vector3 m_targetPosition;
  bool m_isStunned;
  enum SandWormDashBehaviourNew_State__Enum m_state;
};
struct SandWormDashBehaviourNew {
  struct SandWormDashBehaviourNew__Class *klass;
  struct MonitorData *monitor;
  struct SandWormDashBehaviourNew__Fields fields;
};
struct SandWormDashBehaviourNew__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData get_Info;
  VirtualInvokeData PerformSanityCheck;
  VirtualInvokeData get_Status;
  VirtualInvokeData Execute;
  VirtualInvokeData Reset;
  VirtualInvokeData InitializeBehaviourNode;
  VirtualInvokeData CompareTo;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData OnDestroy;
  VirtualInvokeData MoonCleanup;
  VirtualInvokeData Execute_1;
  VirtualInvokeData Reset_1;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData OnReset;
  VirtualInvokeData OnBehaviourTreeInitialize;
  VirtualInvokeData OnExecute;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData CacheSerializedComponents;
  VirtualInvokeData OnEntityInitialized;
};
struct SandWormDashBehaviourNew__StaticFields {
};
struct SandWormDashBehaviourNew__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct SandWormDashBehaviourNew__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct SandWormDashBehaviourNew__VTable vtable;
};

struct SandWormGoToEdgeBehaviourNew__Fields {
  struct EntityBehaviourNode_1_SandWormEntity___Fields _;
  struct MoonVector3 * EdgePosition;
  struct MoonVector3 * EdgePositionNormal;
  struct MoonVector3 * TrackedTargetPosition;
  float MaxAngle;
  float MinDistanceToEdge;
  float MaxSuccessDistance;
  float DistanceToCheckForEdge;
  struct SandWormLocomotion * m_locomotion;
  struct SandWormEntity * m_wormEntity;
  struct Vector3 m_target;
};
struct SandWormGoToEdgeBehaviourNew {
  struct SandWormGoToEdgeBehaviourNew__Class *klass;
  struct MonitorData *monitor;
  struct SandWormGoToEdgeBehaviourNew__Fields fields;
};
struct SandWormGoToEdgeBehaviourNew__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData get_Info;
  VirtualInvokeData PerformSanityCheck;
  VirtualInvokeData get_Status;
  VirtualInvokeData Execute;
  VirtualInvokeData Reset;
  VirtualInvokeData InitializeBehaviourNode;
  VirtualInvokeData CompareTo;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData OnDestroy;
  VirtualInvokeData MoonCleanup;
  VirtualInvokeData Execute_1;
  VirtualInvokeData Reset_1;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData OnReset;
  VirtualInvokeData OnBehaviourTreeInitialize;
  VirtualInvokeData OnExecute;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData CacheSerializedComponents;
  VirtualInvokeData OnEntityInitialized;
};
struct SandWormGoToEdgeBehaviourNew__StaticFields {
};
struct SandWormGoToEdgeBehaviourNew__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct SandWormGoToEdgeBehaviourNew__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct SandWormGoToEdgeBehaviourNew__VTable vtable;
};

struct SandWormShootingBehaviourNew__Fields {
  struct EntityBehaviourNode_1_SandWormEntity___Fields _;
  struct MoonReference_1_UnityEngine_GameObject_ * ShootTarget;
  struct MoonFloat * MinDistanceToTarget;
  struct MoonVector3 * EdgePosition;
  struct MoonVector3 * EdgePositionNormal;
  struct MoonTimeline * ShootingTimeline;
  struct EventTriggerAnimator * ShootingEvent;
  struct PrefabSpawner * ProjectileSpawner;
  float ProjectileSpeed;
  float ProjectileGravity;
  int32_t ProjectileDamage;
  float ProjectileTravelTime;
  bool ShootOnce;
  float RotationRate;
  struct SandWormEntity * m_wormEntity;
  struct SandWormLocomotion * m_locomotion;
  struct Vector2 m_projectileSpeed;
  bool m_lookAtTarget;
  float m_originalHeadRotationSpeedScale;
  struct Vector3 m_edgePositionNormal;
  bool m_isBlocking;
};
struct SandWormShootingBehaviourNew {
  struct SandWormShootingBehaviourNew__Class *klass;
  struct MonitorData *monitor;
  struct SandWormShootingBehaviourNew__Fields fields;
};
struct SandWormShootingBehaviourNew__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData get_Info;
  VirtualInvokeData PerformSanityCheck;
  VirtualInvokeData get_Status;
  VirtualInvokeData Execute;
  VirtualInvokeData Reset;
  VirtualInvokeData InitializeBehaviourNode;
  VirtualInvokeData CompareTo;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData OnDestroy;
  VirtualInvokeData MoonCleanup;
  VirtualInvokeData Execute_1;
  VirtualInvokeData Reset_1;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData OnReset;
  VirtualInvokeData OnBehaviourTreeInitialize;
  VirtualInvokeData OnExecute;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData CacheSerializedComponents;
  VirtualInvokeData OnEntityInitialized;
};
struct SandWormShootingBehaviourNew__StaticFields {
};
struct SandWormShootingBehaviourNew__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct SandWormShootingBehaviourNew__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct SandWormShootingBehaviourNew__VTable vtable;
};

struct SandWormStickOutBehaviourNew__Fields {
  struct EntityBehaviourNode_1_SandWormEntity___Fields _;
  struct MoonReference_1_UnityEngine_GameObject_ * LookTarget;
  struct MoonFloat * MinDistanceToTarget;
  struct MoonVector3 * EdgePosition;
  struct MoonVector3 * EdgePositionNormal;
  float HeadRotationSpeed;
  float Duration;
  float StickAmount;
  float RotationRate;
  struct AnimationCurve * StickHeadOutMovementCurve;
  struct Event_1 * StickHeadOutSound;
  struct Vector3 m_stickOutPosition;
  struct Vector3 m_stickOutNormal;
  struct SandWormLocomotion * m_locomotion;
  bool m_movingToEdge;
  struct Vector3 m_stickOutStartingPos;
  float m_time;
  bool m_hasEdgeAnchor;
  struct SandWormEntity * m_wormEntity;
  bool m_soundPlayed;
  struct Vector3 m_edgePositionNormal;
};
struct SandWormStickOutBehaviourNew {
  struct SandWormStickOutBehaviourNew__Class *klass;
  struct MonitorData *monitor;
  struct SandWormStickOutBehaviourNew__Fields fields;
};
struct SandWormStickOutBehaviourNew__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData get_Info;
  VirtualInvokeData PerformSanityCheck;
  VirtualInvokeData get_Status;
  VirtualInvokeData Execute;
  VirtualInvokeData Reset;
  VirtualInvokeData InitializeBehaviourNode;
  VirtualInvokeData CompareTo;
  VirtualInvokeData get_TaskStatus;
  VirtualInvokeData set_TaskStatus;
  VirtualInvokeData get_ForceReturnTaskStatus;
  VirtualInvokeData set_ForceReturnTaskStatus;
  VirtualInvokeData OnExecuteTask;
  VirtualInvokeData OnInitializeTask;
  VirtualInvokeData OnEnterTask;
  VirtualInvokeData OnExitTask;
  VirtualInvokeData OnResetTask;
  VirtualInvokeData OnDestroy;
  VirtualInvokeData MoonCleanup;
  VirtualInvokeData Execute_1;
  VirtualInvokeData Reset_1;
  VirtualInvokeData OnEnter;
  VirtualInvokeData OnExit;
  VirtualInvokeData OnReset;
  VirtualInvokeData OnBehaviourTreeInitialize;
  VirtualInvokeData OnExecute;
  VirtualInvokeData OnEntityInitialization;
  VirtualInvokeData get_InitOrder;
  VirtualInvokeData get_ShouldPauseLocomotionIsConstant;
  VirtualInvokeData ShouldPauseLocomotion;
  VirtualInvokeData CacheSerializedComponents;
  VirtualInvokeData OnEntityInitialized;
};
struct SandWormStickOutBehaviourNew__StaticFields {
};
struct SandWormStickOutBehaviourNew__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct SandWormStickOutBehaviourNew__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct SandWormStickOutBehaviourNew__VTable vtable;
};

struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields {
  struct MonoBehaviour__Fields _;
  struct Texture2D * Missing;
  bool ThrowMissingError;
  struct List_1_ScreenshotIcon_EnemyType_ * m_keys;
  struct List_1_UnityEngine_Texture2D_ * m_values;
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ * m_dictionary;
};
struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields fields;
};
struct EnemiesIconsCollection__Fields {
  struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields _;
};
struct EnemiesIconsCollection {
  struct EnemiesIconsCollection__Class *klass;
  struct MonitorData *monitor;
  struct EnemiesIconsCollection__Fields fields;
};
struct __declspec(align(8)) List_1_ScreenshotIcon_EnemyType___Fields {
  struct ScreenshotIcon_EnemyType__Enum__Array * _items;
  int32_t _size;
  int32_t _version;
  struct Object * _syncRoot;
};
struct List_1_ScreenshotIcon_EnemyType_ {
  struct List_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct List_1_ScreenshotIcon_EnemyType___Fields fields;
};
struct ScreenshotIcon_EnemyType__Enum__Array {
  struct ScreenshotIcon_EnemyType__Enum__Array__Class *klass;
  struct MonitorData *monitor;
  struct Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  enum ScreenshotIcon_EnemyType__Enum vector[32];
};
struct IEnumerator_1_ScreenshotIcon_EnemyType_ {
  struct IEnumerator_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
};
struct __declspec(align(8)) Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields {
  struct Int32__Array * buckets;
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Array * entries;
  int32_t count;
  int32_t version;
  int32_t freeList;
  int32_t freeCount;
  struct IEqualityComparer_1_ScreenshotIcon_EnemyType_ * comparer;
  struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ * keys;
  struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ * values;
  struct Object * _syncRoot;
};
struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields fields;
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  int32_t hashCode;
  int32_t next;
  enum ScreenshotIcon_EnemyType__Enum key;
  struct Texture2D * value;
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Boxed {
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ fields;
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Array {
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Array__Class *klass;
  struct MonitorData *monitor;
  struct Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ vector[32];
};
struct IEqualityComparer_1_ScreenshotIcon_EnemyType_ {
  struct IEqualityComparer_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
};
struct __declspec(align(8)) Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields {
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ * dictionary;
};
struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields fields;
};
struct __declspec(align(8)) Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields {
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ * dictionary;
};
struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Fields fields;
};
struct ICollection_1_ScreenshotIcon_EnemyType_ {
  struct ICollection_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  enum ScreenshotIcon_EnemyType__Enum key;
  struct Texture2D * value;
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Boxed {
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ fields;
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Array {
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Array__Class *klass;
  struct MonitorData *monitor;
  struct Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ vector[32];
};
struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D_ {
  struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class *klass;
  struct MonitorData *monitor;
};
struct IEnumerable_1_ScreenshotIcon_EnemyType_ {
  struct IEnumerable_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
};
struct IEnumerator_1_ScreenshotIcon_EnemyType___VTable {
  VirtualInvokeData get_Current;
};
struct IEnumerator_1_ScreenshotIcon_EnemyType___StaticFields {
};
struct IEnumerator_1_ScreenshotIcon_EnemyType___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct IEnumerator_1_ScreenshotIcon_EnemyType___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct IEnumerator_1_ScreenshotIcon_EnemyType___VTable vtable;
};
struct List_1_ScreenshotIcon_EnemyType___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData get_Item;
  VirtualInvokeData set_Item;
  VirtualInvokeData IndexOf;
  VirtualInvokeData Insert;
  VirtualInvokeData RemoveAt;
  VirtualInvokeData get_Count;
  VirtualInvokeData System_Collections_Generic_ICollection_T__get_IsReadOnly;
  VirtualInvokeData Add;
  VirtualInvokeData Clear;
  VirtualInvokeData Contains;
  VirtualInvokeData CopyTo;
  VirtualInvokeData Remove;
  VirtualInvokeData System_Collections_Generic_IEnumerable_T__GetEnumerator;
  VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
  VirtualInvokeData System_Collections_IList_get_Item;
  VirtualInvokeData System_Collections_IList_set_Item;
  VirtualInvokeData System_Collections_IList_Add;
  VirtualInvokeData System_Collections_IList_Contains;
  VirtualInvokeData Clear_1;
  VirtualInvokeData System_Collections_IList_get_IsReadOnly;
  VirtualInvokeData System_Collections_IList_get_IsFixedSize;
  VirtualInvokeData System_Collections_IList_IndexOf;
  VirtualInvokeData System_Collections_IList_Insert;
  VirtualInvokeData System_Collections_IList_Remove;
  VirtualInvokeData RemoveAt_1;
  VirtualInvokeData System_Collections_ICollection_CopyTo;
  VirtualInvokeData get_Count_1;
  VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
  VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
  VirtualInvokeData get_Item_1;
  VirtualInvokeData get_Count_2;
};
struct List_1_ScreenshotIcon_EnemyType___StaticFields {
  struct ScreenshotIcon_EnemyType__Enum__Array * _emptyArray;
};
struct List_1_ScreenshotIcon_EnemyType___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct List_1_ScreenshotIcon_EnemyType___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct List_1_ScreenshotIcon_EnemyType___VTable vtable;
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct Dictionary_2_TKey_TValue_Entry_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct IEqualityComparer_1_ScreenshotIcon_EnemyType___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData GetHashCode;
};
struct IEqualityComparer_1_ScreenshotIcon_EnemyType___StaticFields {
};
struct IEqualityComparer_1_ScreenshotIcon_EnemyType___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct IEqualityComparer_1_ScreenshotIcon_EnemyType___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct IEqualityComparer_1_ScreenshotIcon_EnemyType___VTable vtable;
};
struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData get_Count;
  VirtualInvokeData System_Collections_Generic_ICollection_TKey__get_IsReadOnly;
  VirtualInvokeData System_Collections_Generic_ICollection_TKey__Add;
  VirtualInvokeData System_Collections_Generic_ICollection_TKey__Clear;
  VirtualInvokeData System_Collections_Generic_ICollection_TKey__Contains;
  VirtualInvokeData CopyTo;
  VirtualInvokeData System_Collections_Generic_ICollection_TKey__Remove;
  VirtualInvokeData System_Collections_Generic_IEnumerable_TKey__GetEnumerator;
  VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
  VirtualInvokeData System_Collections_ICollection_CopyTo;
  VirtualInvokeData get_Count_1;
  VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
  VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
  VirtualInvokeData get_Count_2;
};
struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct Dictionary_2_TKey_TValue_KeyCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData get_Count;
  VirtualInvokeData System_Collections_Generic_ICollection_TValue__get_IsReadOnly;
  VirtualInvokeData System_Collections_Generic_ICollection_TValue__Add;
  VirtualInvokeData System_Collections_Generic_ICollection_TValue__Clear;
  VirtualInvokeData System_Collections_Generic_ICollection_TValue__Contains;
  VirtualInvokeData CopyTo;
  VirtualInvokeData System_Collections_Generic_ICollection_TValue__Remove;
  VirtualInvokeData System_Collections_Generic_IEnumerable_TValue__GetEnumerator;
  VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
  VirtualInvokeData System_Collections_ICollection_CopyTo;
  VirtualInvokeData get_Count_1;
  VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
  VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
  VirtualInvokeData get_Count_2;
};
struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct Dictionary_2_TKey_TValue_ValueCollection_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct ICollection_1_ScreenshotIcon_EnemyType___VTable {
  VirtualInvokeData get_Count;
  VirtualInvokeData get_IsReadOnly;
  VirtualInvokeData Add;
  VirtualInvokeData Clear;
  VirtualInvokeData Contains;
  VirtualInvokeData CopyTo;
  VirtualInvokeData Remove;
};
struct ICollection_1_ScreenshotIcon_EnemyType___StaticFields {
};
struct ICollection_1_ScreenshotIcon_EnemyType___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct ICollection_1_ScreenshotIcon_EnemyType___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct ICollection_1_ScreenshotIcon_EnemyType___VTable vtable;
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData get_Current;
};
struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct IEnumerator_1_KeyValuePair_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct IEnumerable_1_ScreenshotIcon_EnemyType___VTable {
  VirtualInvokeData GetEnumerator;
};
struct IEnumerable_1_ScreenshotIcon_EnemyType___StaticFields {
};
struct IEnumerable_1_ScreenshotIcon_EnemyType___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct IEnumerable_1_ScreenshotIcon_EnemyType___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct IEnumerable_1_ScreenshotIcon_EnemyType___VTable vtable;
};
struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData get_Item;
  VirtualInvokeData set_Item;
  VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Keys;
  VirtualInvokeData System_Collections_Generic_IDictionary_TKey_TValue__get_Values;
  VirtualInvokeData ContainsKey;
  VirtualInvokeData Add;
  VirtualInvokeData Remove;
  VirtualInvokeData TryGetValue;
  VirtualInvokeData get_Count;
  VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___get_IsReadOnly;
  VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Add;
  VirtualInvokeData Clear;
  VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Contains;
  VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___CopyTo;
  VirtualInvokeData System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Remove;
  VirtualInvokeData System_Collections_Generic_IEnumerable_System_Collections_Generic_KeyValuePair_TKey_TValue___GetEnumerator;
  VirtualInvokeData System_Collections_IEnumerable_GetEnumerator;
  VirtualInvokeData System_Collections_IDictionary_get_Item;
  VirtualInvokeData System_Collections_IDictionary_set_Item;
  VirtualInvokeData System_Collections_IDictionary_get_Keys;
  VirtualInvokeData System_Collections_IDictionary_get_Values;
  VirtualInvokeData System_Collections_IDictionary_Contains;
  VirtualInvokeData System_Collections_IDictionary_Add;
  VirtualInvokeData Clear_1;
  VirtualInvokeData System_Collections_IDictionary_get_IsReadOnly;
  VirtualInvokeData System_Collections_IDictionary_get_IsFixedSize;
  VirtualInvokeData System_Collections_IDictionary_GetEnumerator;
  VirtualInvokeData System_Collections_IDictionary_Remove;
  VirtualInvokeData System_Collections_ICollection_CopyTo;
  VirtualInvokeData get_Count_1;
  VirtualInvokeData System_Collections_ICollection_get_SyncRoot;
  VirtualInvokeData System_Collections_ICollection_get_IsSynchronized;
  VirtualInvokeData ContainsKey_1;
  VirtualInvokeData TryGetValue_1;
  VirtualInvokeData get_Item_1;
  VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Keys;
  VirtualInvokeData System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Values;
  VirtualInvokeData get_Count_2;
  VirtualInvokeData GetObjectData;
  VirtualInvokeData OnDeserialization;
  VirtualInvokeData GetObjectData_1;
  VirtualInvokeData OnDeserialization_1;
};
struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct Dictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData EnsureListMatchesEnum;
};
struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields {
};
struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct EnumDictionary_2_ScreenshotIcon_EnemyType_UnityEngine_Texture2D___VTable vtable;
};
struct EnemiesIconsCollection__VTable {
  VirtualInvokeData Equals;
  VirtualInvokeData Finalize;
  VirtualInvokeData GetHashCode;
  VirtualInvokeData ToString;
  VirtualInvokeData OnBeforeSerialize;
  VirtualInvokeData OnAfterDeserialize;
  VirtualInvokeData OnValidate;
  VirtualInvokeData EnsureListMatchesEnum;
};
struct EnemiesIconsCollection__StaticFields {
};
struct EnemiesIconsCollection__Class {
  struct Il2CppClass_0 _0;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
  struct EnemiesIconsCollection__StaticFields *static_fields;
  const Il2CppRGCTXData *rgctx_data;
  struct Il2CppClass_1 _1;
  struct EnemiesIconsCollection__VTable vtable;
};

struct EnemiesSettings__Fields {
  struct MonoBehaviour__Fields _;
  struct EnemiesIconsCollection * Icons;
  struct EntitiesTypeDictionary * TypeDictionary;
  struct EntityPrefabDictionary * PrefabDictionary;
};
struct EnemiesSettings {
  struct EnemiesSettings__Class *klass;
  struct MonitorData *monitor;
  struct EnemiesSettings__Fields fields;
};
struct EnumTypeDictionary_1_ScreenshotIcon_EnemyType___Fields {
  struct MonoBehaviour__Fields _;
  enum ScreenshotIcon_EnemyType__Enum Missing;
  struct List_1_System_String_ * m_keys;
  struct List_1_ScreenshotIcon_EnemyType_ * m_values;
  struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType_ * m_dictionary;
};
struct EnumTypeDictionary_1_ScreenshotIcon_EnemyType_ {
  struct EnumTypeDictionary_1_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct EnumTypeDictionary_1_ScreenshotIcon_EnemyType___Fields fields;
};
struct EntitiesTypeDictionary__Fields {
  struct EnumTypeDictionary_1_ScreenshotIcon_EnemyType___Fields _;
};
struct EntitiesTypeDictionary {
  struct EntitiesTypeDictionary__Class *klass;
  struct MonitorData *monitor;
  struct EntitiesTypeDictionary__Fields fields;
};
struct __declspec(align(8)) Dictionary_2_System_Type_ScreenshotIcon_EnemyType___Fields {
  struct Int32__Array * buckets;
  struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType___Array * entries;
  int32_t count;
  int32_t version;
  int32_t freeList;
  int32_t freeCount;
  struct IEqualityComparer_1_System_Type_ * comparer;
  struct Dictionary_2_TKey_TValue_KeyCollection_System_Type_ScreenshotIcon_EnemyType_ * keys;
  struct Dictionary_2_TKey_TValue_ValueCollection_System_Type_ScreenshotIcon_EnemyType_ * values;
  struct Object * _syncRoot;
};
struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType_ {
  struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType___Fields fields;
};
struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType_ {
  int32_t hashCode;
  int32_t next;
  struct Type * key;
  enum ScreenshotIcon_EnemyType__Enum value;
};
struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType___Boxed {
  struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType_ fields;
};
struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType___Array {
  struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType___Array__Class *klass;
  struct MonitorData *monitor;
  struct Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  struct Dictionary_2_TKey_TValue_Entry_System_Type_ScreenshotIcon_EnemyType_ vector[32];
};
struct __declspec(align(8)) Dictionary_2_TKey_TValue_KeyCollection_System_Type_ScreenshotIcon_EnemyType___Fields {
  struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType_ * dictionary;
};
struct Dictionary_2_TKey_TValue_KeyCollection_System_Type_ScreenshotIcon_EnemyType_ {
  struct Dictionary_2_TKey_TValue_KeyCollection_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_KeyCollection_System_Type_ScreenshotIcon_EnemyType___Fields fields;
};
struct __declspec(align(8)) Dictionary_2_TKey_TValue_ValueCollection_System_Type_ScreenshotIcon_EnemyType___Fields {
  struct Dictionary_2_System_Type_ScreenshotIcon_EnemyType_ * dictionary;
};
struct Dictionary_2_TKey_TValue_ValueCollection_System_Type_ScreenshotIcon_EnemyType_ {
  struct Dictionary_2_TKey_TValue_ValueCollection_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_TKey_TValue_ValueCollection_System_Type_ScreenshotIcon_EnemyType___Fields fields;
};
struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType_ {
  struct Type * key;
  enum ScreenshotIcon_EnemyType__Enum value;
};
struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType___Boxed {
  struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType_ fields;
};
struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType___Array {
  struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType___Array__Class *klass;
  struct MonitorData *monitor;
  struct Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  struct KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType_ vector[32];
};
struct IEnumerator_1_KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType_ {
  struct IEnumerator_1_KeyValuePair_2_System_Type_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
};
struct EntityPrefabDictionary__Fields {
  struct MonoBehaviour__Fields _;
  enum ScreenshotIcon_EnemyType__Enum Missing;
  struct List_1_UnityEngine_GameObject_ * m_keys;
  struct List_1_ScreenshotIcon_EnemyType_ * m_values;
  struct Dictionary_2_UnityEngine_GameObject_ScreenshotIcon_EnemyType_ * m_dictionary;
};
struct EntityPrefabDictionary {
  struct EntityPrefabDictionary__Class *klass;
  struct MonitorData *monitor;
  struct EntityPrefabDictionary__Fields fields;
};
struct __declspec(align(8)) Dictionary_2_UnityEngine_GameObject_ScreenshotIcon_EnemyType___Fields {
  struct Int32__Array * buckets;
  struct Dictionary_2_TKey_TValue_Entry_UnityEngine_GameObject_ScreenshotIcon_EnemyType___Array * entries;
  int32_t count;
  int32_t version;
  int32_t freeList;
  int32_t freeCount;
  struct IEqualityComparer_1_UnityEngine_GameObject_ * comparer;
  struct Dictionary_2_TKey_TValue_KeyCollection_UnityEngine_GameObject_ScreenshotIcon_EnemyType_ * keys;
  struct Dictionary_2_TKey_TValue_ValueCollection_UnityEngine_GameObject_ScreenshotIcon_EnemyType_ * values;
  struct Object * _syncRoot;
};
struct Dictionary_2_UnityEngine_GameObject_ScreenshotIcon_EnemyType_ {
  struct Dictionary_2_UnityEngine_GameObject_ScreenshotIcon_EnemyType___Class *klass;
  struct MonitorData *monitor;
  struct Dictionary_2_UnityEngine_GameObject_ScreenshotIcon_EnemyType___Fields fields;
};